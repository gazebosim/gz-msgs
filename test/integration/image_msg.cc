/*
 * Copyright (C) 2019 Open Source Robotics Foundation
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

#include "ignition/msgs/image.pb.h"

/////////////////////////////////////////////////
TEST(Image, PixelFormat)
{
  // Check that pixel format enum is properly set
  ignition::msgs::Image msg;
  EXPECT_EQ(ignition::msgs::PixelFormatType::UNKNOWN_PIXEL_FORMAT,
    msg.pixel_format());

  msg.set_pixel_format(ignition::msgs::PixelFormatType::RGB_INT8);
  EXPECT_EQ(ignition::msgs::PixelFormatType::RGB_INT8,
    msg.pixel_format());
}
