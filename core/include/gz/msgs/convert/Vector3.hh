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
#ifndef GZ_MSGS_CONVERT_VECTOR3_HH_
#define GZ_MSGS_CONVERT_VECTOR3_HH_

#include <gz/msgs/Converter.hh>

// Message Headers
#include "gz/msgs/vector3d.pb.h"

// Data Headers
#include <gz/math/Vector3.hh>

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Set(
    gz::msgs::Vector3d *_msg, const gz::math::Vector3d &_data)
{
  _msg->set_x(_data.X());
  _msg->set_y(_data.Y());
  _msg->set_z(_data.Z());
}

template<>
inline void Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Set(
    gz::math::Vector3d *_data, const gz::msgs::Vector3d &_msg)
{
  _data->Set(_msg.x(), _msg.y(), _msg.z());
}

inline gz::msgs::Vector3d Convert(const gz::math::Vector3d &_data)
{
  return Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Convert(_data);
}

inline gz::math::Vector3d Convert(const gz::msgs::Vector3d &_msg)
{
  return Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Convert(_msg);
}
}  // namespace
}  // namespace gz::msgs
#endif  // GZ_MSGS_CONVERT_VECTOR3_HH_
