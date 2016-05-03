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
#include <cstddef>
#include <algorithm>
#include "ignition/msgs/MessageTypes.hh"
#include "ignition/msgs/Factory.hh"

using namespace ignition;

/////////////////////////////////////////////////
TEST(FactoryTest, Type)
{
  std::vector<std::string> types;
  msgs::Factory::Types(types);
  EXPECT_FALSE(types.empty());
  EXPECT_TRUE(std::find(types.begin(), types.end(),
        std::string("ign_msgs.Vector3d")) !=
      types.end());
}

/////////////////////////////////////////////////
TEST(FactoryTest, New)
{
  auto msg = msgs::Factory::New<msgs::Vector3d>("ign_msgs.Vector3d");

  EXPECT_TRUE(msg.get() != nullptr);

  msg->set_x(1.0);
  msg->set_y(2.0);
  msg->set_z(3.0);

  auto msgFilled = msgs::Factory::New<msgs::Vector3d>(
      "ign_msgs.Vector3d", "x: 1.0, y: 2.0, z: 3.0");

  EXPECT_EQ(msg->x(), msgFilled->x());
  EXPECT_EQ(msg->y(), msgFilled->y());
  EXPECT_EQ(msg->z(), msgFilled->z());
}
