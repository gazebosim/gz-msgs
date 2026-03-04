/*
 * Copyright (C) 2024 Open Source Robotics Foundation
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

#include <filesystem>

#include <google/protobuf/stubs/logging.h>

#include "gz/msgs/Factory.hh"

static constexpr const char * kMsgsTestPath = GZ_MSGS_TEST_PATH;

TEST(FactoryTest, DynamicFactory)
{
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.Bytes"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BazMessage"));

  // Test loading an invalid path
  {
    std::filesystem::path test_path(kMsgsTestPath);
    std::string paths = (test_path / "desc" / "does_not_exist.desc").string();
    gz::msgs::Factory::LoadDescriptors(paths);
  }
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.Bytes"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BazMessage"));

  // Test loading an incorrect extension
  {
    std::filesystem::path test_path(kMsgsTestPath);
    std::string paths = (test_path / "desc" / "testing.invalid").string();
    gz::msgs::Factory::LoadDescriptors(paths);
  }
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.Bytes"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BazMessage"));

  // Test loading a file with invalid content
  {
    std::filesystem::path test_path(kMsgsTestPath);
    std::string paths = (test_path / "desc" / "testing.proto").string();
    gz::msgs::Factory::LoadDescriptors(paths);
  }
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarBytes"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BazMessage"));

  // Load a valid descriptor file with one message type
  {
    std::filesystem::path test_path(kMsgsTestPath);
    std::string paths = (test_path / "desc" / "stringmsg.desc").string();
    gz::msgs::Factory::LoadDescriptors(paths);
  }

  EXPECT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.Bytes"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_EQ(nullptr, gz::msgs::Factory::New("testing.BazMessage"));

  // Load a directory
  {
    std::filesystem::path test_path(kMsgsTestPath);
    std::string paths = (test_path / "desc").string();
    gz::msgs::Factory::LoadDescriptors(paths);
  }

  EXPECT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("testing.FooBytes"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("testing.FooMessage"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("testing.BarMessage"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("testing.BazMessage"));
}

TEST(FactoryTest, NoDuplicateDescriptors)
{
  // Regression test for https://github.com/gazebosim/gz-msgs/issues/460
  // When the same .gz_desc file is reachable via both GZ_DESCRIPTOR_PATH
  // and the global share directory, the DynamicFactory used to print:
  //   [libprotobuf ERROR] File already exists in database: ...
  // The fix silently skips proto definitions already present in the pool.

  std::filesystem::path test_path(kMsgsTestPath);
  std::string path = (test_path / "desc" / "stringmsg.desc").string();

#ifdef _WIN32
  std::string paths = path + ";" + path;
#else
  std::string paths = path + ":" + path;
#endif

  // SetLogHandler requires a plain function pointer (no captures), so use a
  // static flag to detect ERROR-level messages from libprotobuf during loading.
  static bool s_protobuf_error_seen;
  s_protobuf_error_seen = false;
  auto * old_handler = google::protobuf::SetLogHandler(
    [](google::protobuf::LogLevel level, const char *, int,
       const std::string &) {
      if (level == google::protobuf::LOGLEVEL_ERROR) {
        s_protobuf_error_seen = true;
      }
    });

  // Loading the same descriptor twice must not cause protobuf errors.
  // The second occurrence is skipped because the protos are already in the pool.
  gz::msgs::Factory::LoadDescriptors(paths);

  google::protobuf::SetLogHandler(old_handler);

  EXPECT_FALSE(s_protobuf_error_seen)
    << "libprotobuf ERROR emitted during duplicate descriptor load";

  // The message type must remain accessible after duplicate loading.
  EXPECT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
}
