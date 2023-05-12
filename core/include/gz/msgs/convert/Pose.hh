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
#ifndef GZ_MSGS_CONVERT_POSE_HH_
#define GZ_MSGS_CONVERT_POSE_HH_

#include <gz/msgs/Converter.hh>
#include <gz/msgs/convert/Vector3.hh>
#include <gz/msgs/convert/Quaternion.hh>

// Message Headers
#include "gz/msgs/details/quaternion.pb.h"
#include "gz/msgs/pose.pb.h"

// Data Headers
#include <gz/math/Pose3.hh>

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Pose, gz::math::Pose3d>::Set(gz::msgs::Pose *_msg, const gz::math::Pose3d &_data)
{
  Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Set(_msg->mutable_position(), _data.Pos());
  Converter<gz::msgs::Quaternion, gz::math::Quaterniond>::Set(_msg->mutable_orientation(), _data.Rot());
}

template<>
inline void Converter<gz::msgs::Pose, gz::math::Pose3d>::Set(gz::math::Pose3d *_data, const gz::msgs::Pose &_msg)
{
  auto pos = Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Convert(_msg.position());
  auto orientation = Converter<gz::msgs::Quaternion, gz::math::Quaterniond>::Convert(_msg.orientation());
  _data->Set(pos, orientation);
}

inline gz::msgs::Pose Convert(const gz::math::Pose3d &_data)
{
  return Converter<gz::msgs::Pose, gz::math::Pose3d>::Convert(_data);
}

inline gz::math::Pose3d Convert(const gz::msgs::Pose &_msg)
{
  return Converter<gz::msgs::Pose, gz::math::Pose3d>::Convert(_msg);
}


}  // namespce
}  // namespace gz::msgs

#endif  // GZ_MSGS_CONVERT_VECTOR3_HH_
