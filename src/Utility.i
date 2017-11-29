/*
 * Copyright (C) 2017 Open Source Robotics Foundation
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

%module utility
%{
#include <ignition/msgs/Utility.hh>
%}

namespace ignition
{
  namespace msgs
  {
/*    ignition::math::Vector3d Convert(const msgs::Vector3d &_v);
    ignition::math::Vector2d Convert(const msgs::Vector2d &_v);
    ignition::math::Quaterniond Convert(const msgs::Quaternion &_q);
    ignition::math::Pose3d Convert(const msgs::Pose &_p);
    math::Color Convert(const msgs::Color &_c);
    ignition::math::Planed Convert(const msgs::PlaneGeom &_p);
    math::Inertiald Convert(const msgs::Inertial &_i);
    */
    std::string Convert(const msgs::StringMsg &_m);
    bool Convert(const msgs::Boolean &_m);
    int32_t Convert(const msgs::Int32 &_m);
    uint32_t Convert(const msgs::UInt32 &_m);
    int64_t Convert(const msgs::Int64 &_m);
    uint64_t Convert(const msgs::UInt64 &_m);
    double Convert(const msgs::Double &_m);
    float Convert(const msgs::Float &_m);
/*    msgs::Vector3d Convert(const ignition::math::Vector3d &_v);
    msgs::Vector2d Convert(const ignition::math::Vector2d &_v);
    msgs::Quaternion Convert(const ignition::math::Quaterniond &_q);
    msgs::Pose Convert(const ignition::math::Pose3d &_p);
    msgs::Color Convert(const math::Color &_c);
    msgs::Inertial Convert(const math::Inertiald &_i);
    msgs::Inertial Convert(const math::MassMatrix3d &_m);
    msgs::PlaneGeom Convert(const ignition::math::Planed &_p);
*/
    msgs::StringMsg Convert(const std::string &_s);
    msgs::Boolean Convert(const bool &_b);
    msgs::Int32 Convert(const int32_t &_i);
    msgs::UInt32 Convert(const uint32_t &_u);
    msgs::Int64 Convert(const int64_t &_i);
    msgs::UInt64 Convert(const uint64_t &_u);
    msgs::Double Convert(const double &_d);
    msgs::Float Convert(const float &_f);
/*    msgs::Joint::Type ConvertJointType(const std::string &_str);
    std::string ConvertJointType(const msgs::Joint::Type &_type);
    msgs::Geometry::Type ConvertGeometryType(const std::string &_str);
    std::string ConvertGeometryType(const msgs::Geometry::Type _type);
    msgs::Material::ShaderType ConvertShaderType(const std::string &_str);
    std::string ConvertShaderType(const msgs::Material::ShaderType &_type);
    void Set(msgs::Vector3d *_pt, const ignition::math::Vector3d &_v);
    void Set(msgs::Vector2d *_pt, const ignition::math::Vector2d &_v);
    void Set(msgs::Quaternion *_q, const ignition::math::Quaterniond &_v);
    void Set(msgs::Pose *_p, const ignition::math::Pose3d &_v);
    void Set(msgs::Color *_c, const math::Color &_v);
    void Set(msgs::Inertial *_i, const math::Inertiald &_m);
    void Set(msgs::Inertial *_i, const math::MassMatrix3d &_m);
    void Set(msgs::PlaneGeom *_p, const ignition::math::Planed &_v);
    void Set(msgs::StringMsg *_p, const std::string &_v);
    void Set(msgs::Boolean *_p, const bool &_v);
    void Set(msgs::Int32 *_p, const int32_t &_v);
    void Set(msgs::UInt32 *_p, const uint32_t &_v);
    void Set(msgs::Int64 *_p, const int64_t &_v);
    void Set(msgs::UInt64 *_p, const uint64_t &_v);
    void Set(msgs::Double *_p, const double &_v);
    void Set(msgs::Float *_p, const float &_v);
*/
  }
}
