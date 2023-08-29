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

#include "ignition/msgs/test_config.h"
#include "ignition/msgs/MessageTypes.hh"
#include "ignition/msgs/Factory.hh"

using Factory = ignition::msgs::Factory;
using Vector3d = ignition::msgs::Vector3d;

/////////////////////////////////////////////////
TEST(FactoryTest, Type)
{
  std::vector<std::string> types;
  Factory::Types(types);
  EXPECT_FALSE(types.empty());
  EXPECT_TRUE(std::find(types.begin(), types.end(),
        std::string("ign_msgs.Vector3d")) !=
      types.end());
}

/////////////////////////////////////////////////
TEST(FactoryTest, New)
{
  // Correct call, using periods, fully qualified
  auto msg = Factory::New<Vector3d>("ignition.msgs.Vector3d");

  ASSERT_TRUE(msg.get() != nullptr);

  msg->set_x(1.0);
  msg->set_y(2.0);
  msg->set_z(3.0);

  auto msgFilled = Factory::New<Vector3d>(
      "ign_msgs.Vector3d", "x: 1.0, y: 2.0, z: 3.0");
  ASSERT_TRUE(msgFilled.get() != nullptr);

  EXPECT_DOUBLE_EQ(msg->x(), msgFilled->x());
  EXPECT_DOUBLE_EQ(msg->y(), msgFilled->y());
  EXPECT_DOUBLE_EQ(msg->z(), msgFilled->z());

  // Various other supported ways of specifying gz.msgs
  msg = Factory::New<Vector3d>("ign_msgs.Vector3d");
  EXPECT_TRUE(msg.get() != nullptr);

  msg = Factory::New<Vector3d>(".ignition.msgs.Vector3d");
  EXPECT_TRUE(msg.get() != nullptr);
}

/////////////////////////////////////////////////
TEST(FactoryTest, NewDynamicFactory)
{
  std::string paths;

  auto msg = Factory::New("example.msgs.StringMsg");
  EXPECT_TRUE(msg.get() == nullptr);

  paths =
      PROJECT_SOURCE_PATH "/test/desc:"
      PROJECT_SOURCE_PATH "/test";
  Factory::LoadDescriptors(paths);

  msg = Factory::New("example.msgs.StringMsg");
  EXPECT_TRUE(msg.get() != nullptr);
}

/////////////////////////////////////////////////
TEST(FactoryTest, NewAllRegisteredTypes)
{
  std::vector<std::string> types;
  Factory::Types(types);
  EXPECT_FALSE(types.empty());

  for (const auto &type : types)
  {
    auto msg = Factory::New(type);
    ASSERT_NE(nullptr, msg.get()) << type;
  }
}

/////////////////////////////////////////////////
TEST(FactoryTest, MultipleMessagesInAProto)
{
  auto typesInSameFile =
  {
    "ign_msgs.SerializedEntityMap",
    "ign_msgs.SerializedStateMap",
    "ign_msgs.SerializedStepMap"
  };

  std::vector<std::string> types;
  Factory::Types(types);
  EXPECT_FALSE(types.empty());

  for (auto type : typesInSameFile)
  {
    // Check all types are registered
    EXPECT_NE(std::find(types.begin(), types.end(), std::string(type)),
        types.end()) << type;

    // Check all types can be newed
    auto msg = Factory::New(type);
    EXPECT_NE(nullptr, msg.get()) << type;
  }

  // Compile-time check that pointer types exist
  {
    ignition::msgs::SerializedEntityMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedEntityMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::SerializedEntityMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedEntityMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }

  {
    ignition::msgs::SerializedStateMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedStateMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::SerializedStateMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedStateMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }

  {
    ignition::msgs::SerializedStepMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedStepMapUniquePtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::SerializedStepMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
  {
    ignition::msgs::ConstSerializedStepMapSharedPtr ptr{nullptr};
    EXPECT_EQ(nullptr, ptr);
  }
}
