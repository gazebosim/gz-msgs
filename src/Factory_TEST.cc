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

#include "gz/msgs/test_config.h"
#include "gz/msgs/MessageTypes.hh"
#include "gz/msgs/Factory.hh"

using namespace gz;

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

  paths =
      PROJECT_SOURCE_PATH "/test/desc:"
      PROJECT_SOURCE_PATH "/test";
  msgs::Factory::LoadDescriptors(paths);

  msg = msgs::Factory::New("example.msgs.StringMsg");
  EXPECT_TRUE(msg.get() != nullptr);
}
