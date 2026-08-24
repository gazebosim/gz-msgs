/*
 * Copyright (C) 2026 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <gtest/gtest.h>

#include <google/protobuf/descriptor.pb.h>

#include <filesystem>
#include <fstream>

#include "gz/msgs/MessageFactory.hh"

namespace {

//////////////////////////////////////////////////
/// \brief Serialize a descriptor set holding a single file to _path.
void WriteDescriptorSet(const std::filesystem::path &_path,
                        const google::protobuf::FileDescriptorProto &_file)
{
  google::protobuf::FileDescriptorSet fileSet;
  *fileSet.add_file() = _file;
  std::ofstream ofs(_path, std::ios::binary);
  ASSERT_TRUE(fileSet.SerializeToOstream(&ofs));
}
}  // namespace

/////////////////////////////////////////////////
/// \brief A descriptor file whose import could not be resolved must remain
/// retryable: once the descriptor file providing the missing dependency has
/// been loaded, reloading the first file must succeed. This guards the
/// descriptor file dedup logic, which must not record a file whose
/// descriptors did not all reach the pool.
TEST(FactoryDescriptorRetryTest, ReloadAfterMissingImport)
{
  const auto dir = std::filesystem::path(::testing::TempDir()) /
      "gz_msgs_factory_descriptor_retry";
  std::filesystem::create_directories(dir);

  // b.proto: package b.msgs; message Bar { int32 x = 1; }
  google::protobuf::FileDescriptorProto bFile;
  bFile.set_name("b.proto");
  bFile.set_package("b.msgs");
  bFile.set_syntax("proto3");
  auto *bar = bFile.add_message_type();
  bar->set_name("Bar");
  auto *x = bar->add_field();
  x->set_name("x");
  x->set_number(1);
  x->set_type(google::protobuf::FieldDescriptorProto::TYPE_INT32);
  x->set_label(google::protobuf::FieldDescriptorProto::LABEL_OPTIONAL);

  // a.proto: package a.msgs; import "b.proto";
  // message Foo { b.msgs.Bar bar = 1; }
  google::protobuf::FileDescriptorProto aFile;
  aFile.set_name("a.proto");
  aFile.set_package("a.msgs");
  aFile.set_syntax("proto3");
  aFile.add_dependency("b.proto");
  auto *foo = aFile.add_message_type();
  foo->set_name("Foo");
  auto *barField = foo->add_field();
  barField->set_name("bar");
  barField->set_number(1);
  barField->set_type(google::protobuf::FieldDescriptorProto::TYPE_MESSAGE);
  barField->set_type_name(".b.msgs.Bar");
  barField->set_label(google::protobuf::FieldDescriptorProto::LABEL_OPTIONAL);

  const auto aPath = dir / "a.desc";
  const auto bPath = dir / "b.desc";
  WriteDescriptorSet(aPath, aFile);
  WriteDescriptorSet(bPath, bFile);

  gz::msgs::MessageFactory factory;

  // Loading a.desc fails: its import lives in b.desc, which is unknown yet.
  factory.LoadDescriptors(aPath.string());
  EXPECT_EQ(nullptr, factory.New("a.msgs.Foo"));

  // Load the missing dependency.
  factory.LoadDescriptors(bPath.string());
  ASSERT_NE(nullptr, factory.New("b.msgs.Bar"));

  // Reloading a.desc must now succeed instead of being skipped as a
  // duplicate.
  factory.LoadDescriptors(aPath.string());
  EXPECT_NE(nullptr, factory.New("a.msgs.Foo"));
}
