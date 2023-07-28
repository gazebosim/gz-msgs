/*
 * Copyright (C) 2016 Open Source Robotics Foundation
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

#include <algorithm>
#include <cstddef>
#include <filesystem>

#include "gz/msgs/vector3d.pb.h"
#include "gz/msgs/serialized_map.pb.h"
#include "gz/msgs/Factory.hh"

using namespace gz;

static constexpr const char * kMsgsTestPath = GZ_MSGS_TEST_PATH;

/////////////////////////////////////////////////
TEST(FactoryTest, Type)
{
  std::vector<std::string> types;
  msgs::Factory::Types(types);
  EXPECT_FALSE(types.empty());
  EXPECT_TRUE(std::find(types.begin(), types.end(),
        std::string("gz_msgs.Vector3d")) !=
      types.end());
}

/////////////////////////////////////////////////
TEST(FactoryTest, New)
{
  auto msg = msgs::Factory::New<msgs::Vector3d>("gz_msgs.Vector3d");

  ASSERT_TRUE(msg.get() != nullptr);

  msg->set_x(1.0);
  msg->set_y(2.0);
  msg->set_z(3.0);

  auto msgFilled = msgs::Factory::New<msgs::Vector3d>(
      "gz_msgs.Vector3d", "x: 1.0, y: 2.0, z: 3.0");
  ASSERT_TRUE(msgFilled.get() != nullptr);

  EXPECT_DOUBLE_EQ(msg->x(), msgFilled->x());
  EXPECT_DOUBLE_EQ(msg->y(), msgFilled->y());
  EXPECT_DOUBLE_EQ(msg->z(), msgFilled->z());

  msg = msgs::Factory::New<msgs::Vector3d>("gz.msgs.Vector3d");
  EXPECT_TRUE(msg.get() != nullptr);

  msg = msgs::Factory::New<msgs::Vector3d>(".gz.msgs.Vector3d");
  EXPECT_TRUE(msg.get() != nullptr);
}

/////////////////////////////////////////////////
TEST(FactoryTest, NewDynamicFactory)
{
  std::string paths;

  auto msg = msgs::Factory::New("example.msgs.StringMsg");
  EXPECT_TRUE(msg.get() == nullptr);

  std::filesystem::path test_path(kMsgsTestPath);
  paths += (test_path / "desc").string();
  paths += ":";
  paths += test_path.string();

  msgs::Factory::LoadDescriptors(paths);
  msg = msgs::Factory::New("example.msgs.StringMsg");
  EXPECT_TRUE(msg.get() != nullptr);
}

/////////////////////////////////////////////////
TEST(FactoryTest, NewAllRegisteredTypes)
{
  std::vector<std::string> types;
  msgs::Factory::Types(types);
  EXPECT_FALSE(types.empty());

  for (const auto &type : types)
  {
    auto msg = msgs::Factory::New(type);
    ASSERT_NE(nullptr, msg.get()) << type;
  }
}

/////////////////////////////////////////////////
TEST(FactoryTest, MultipleMessagesInAProto)
{
  auto typesInSameFile =
  {
    "gz_msgs.SerializedEntityMap",
    "gz_msgs.SerializedStateMap",
    "gz_msgs.SerializedStepMap"
  };

  std::vector<std::string> types;
  msgs::Factory::Types(types);
  EXPECT_FALSE(types.empty());

  for (auto type : typesInSameFile)
  {
    // Check all types are registered
    EXPECT_NE(std::find(types.begin(), types.end(), std::string(type)),
        types.end()) << type;

    // Check all types can be newed
    auto msg = msgs::Factory::New(type);
    EXPECT_NE(nullptr, msg.get()) << type;
  }

  // Compile-time check that pointer types exist
  {
    msgs::SerializedEntityMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedEntityMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::SerializedEntityMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedEntityMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }

  {
    msgs::SerializedStateMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedStateMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::SerializedStateMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedStateMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }

  {
    msgs::SerializedStepMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedStepMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::SerializedStepMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    msgs::ConstSerializedStepMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
}
