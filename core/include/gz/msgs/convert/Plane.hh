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
#ifndef GZ_MSGS_CONVERT_PLANE_HH_
#define GZ_MSGS_CONVERT_PLANE_HH_

#include <gz/msgs/Converter.hh>
#include <gz/msgs/convert/Vector2.hh>
#include <gz/msgs/convert/Vector3.hh>

// Message Headers
#include "gz/msgs/planegeom.pb.h"

// Data Headers
#include <gz/math/Plane.hh>

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

/////////////////////////////////
template<>
inline void Converter<gz::msgs::PlaneGeom, gz::math::Planed>::Set(
    gz::msgs::PlaneGeom *_msg, const gz::math::Planed &_data)
{
  Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Set(
        _msg->mutable_normal(), _data.Normal());
  _msg->mutable_size()->set_x(_data.Size().X());
  _msg->mutable_size()->set_y(_data.Size().Y());
  _msg->set_d(_data.Offset());
}

template<>
inline void Converter<gz::msgs::PlaneGeom, gz::math::Planed>::Set(
    gz::math::Planed *_data, const gz::msgs::PlaneGeom &_msg)
{
  _data->Set(
    Converter<gz::msgs::Vector3d, gz::math::Vector3d>::Convert(_msg.normal()),
    Converter<gz::msgs::Vector2d, gz::math::Vector2d>::Convert(_msg.size()),
    _msg.d()
  );
}

inline gz::msgs::PlaneGeom Convert(const gz::math::Planed &_data)
{
  return Converter<gz::msgs::PlaneGeom, gz::math::Planed>::Convert(_data);
}

inline gz::math::Planed Convert(const gz::msgs::PlaneGeom &_msg)
{
  return Converter<gz::msgs::PlaneGeom, gz::math::Planed>::Convert(_msg);
}


}  // namespce
}  // namespace gz::msgs

#endif  // GZ_MSGS_CONVERT_VECTOR3_HH_