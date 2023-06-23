/*
 * Copyright (C) 2023 Open Source Robotics Foundation
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
#ifndef GZ_MSGS_CONVERT_VECTOR2_HH_
#define GZ_MSGS_CONVERT_VECTOR2_HH_

// Message Headers
#include "gz/msgs/vector2d.pb.h"

// Data Headers
#include <gz/math/Vector2.hh>

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

/////////////////////////////////
inline void Set(gz::msgs::Vector2d *_msg, const gz::math::Vector2d &_data)
{
  _msg->set_x(_data.X());
  _msg->set_y(_data.Y());
}

inline void Set(gz::math::Vector2d *_data, const gz::msgs::Vector2d &_msg)
{
  _data->Set(_msg.x(), _msg.y());
}

inline gz::msgs::Vector2d Convert(const gz::math::Vector2d &_data)
{
  gz::msgs::Vector2d ret;
  Set(&ret, _data);
  return ret;
}

inline gz::math::Vector2d Convert(const gz::msgs::Vector2d &_msg)
{
  gz::math::Vector2d ret;
  Set(&ret, _msg);
  return ret;
}
}  // namespce
}  // namespace gz::msgs
#endif  // GZ_MSGS_CONVERT_VECTOR3_HH_
