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
#ifndef IGNITION_MSGS_UTILITY_HH_
#define IGNITION_MSGS_UTILITY_HH_

#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Plane.hh>
#include <ignition/msgs/MessageTypes.hh>
#include <ignition/msgs/System.hh>

namespace ignition
{
  namespace msgs
  {
    /// \brief Convert a msgs::Vector3d to an ignition::math::Vector
    /// \param[in] _v The vector to convert
    /// \return An ignition::math::Vector3d object
    IGNITION_MSGS_VISIBLE
    ignition::math::Vector3d Convert(const msgs::Vector3d &_v);

    /// \brief Convert a msgs::Vector2d to an ignition::math::Vector2d
    /// \param[in] _v The vector2 to convert
    /// \return An ignition::math::Vector2d object
    IGNITION_MSGS_VISIBLE
    ignition::math::Vector2d Convert(const msgs::Vector2d &_v);

    /// \brief Convert a msgs::Quaternion to an ignition::math::Quaterniond
    /// \param[in] _q The quaternion to convert
    /// \return An ignition::math::Quaterniond object
    IGNITION_MSGS_VISIBLE
    ignition::math::Quaterniond Convert(const msgs::Quaternion &_q);

    /// \brief Convert a msgs::Pose to an ignition::math::Pose3d
    /// \param[in] _q The pose to convert
    /// \return An ignition::math::Pose3d object
    IGNITION_MSGS_VISIBLE
    ignition::math::Pose3d Convert(const msgs::Pose &_p);

    /// \brief Convert a msgs::PlaneGeom to an ignition::math::Planed
    /// \param[in] _p The plane to convert
    /// \return An ignition::math::Planed object
    IGNITION_MSGS_VISIBLE
    ignition::math::Planed Convert(const msgs::PlaneGeom &_p);

    /// \brief Convert a ignition::math::Vector3d to a msgs::Vector3d
    /// \param[in] _v The vector to convert
    /// \return A msgs::Vector3d object
    IGNITION_MSGS_VISIBLE
    msgs::Vector3d Convert(const ignition::math::Vector3d &_v);

    /// \brief Convert a ignition::math::Vector2d to a msgs::Vector2d
    /// \param[in] _v The vector to convert
    /// \return A msgs::Vector2d object
    IGNITION_MSGS_VISIBLE
    msgs::Vector2d Convert(const ignition::math::Vector2d &_v);

    /// \brief Convert a ignition::math::Quaterniond to a msgs::Quaternion
    /// \param[in] _q The quaternion to convert
    /// \return A msgs::Quaternion object
    IGNITION_MSGS_VISIBLE
    msgs::Quaternion Convert(const ignition::math::Quaterniond &_q);

    /// \brief Convert a ignition::math::Pose3d to a msgs::Pose
    /// \param[in] _p The pose to convert
    /// \return A msgs::Pose object
    IGNITION_MSGS_VISIBLE
    msgs::Pose Convert(const ignition::math::Pose3d &_p);

    /// \brief Convert a ignition::math::Planed to a msgs::PlaneGeom
    /// \param[in] _p The plane to convert
    /// \return A msgs::PlaneGeom object
    IGNITION_MSGS_VISIBLE
    msgs::PlaneGeom Convert(const ignition::math::Planed &_p);

    /// \brief Set a msgs::Vector3d from an ignition::math::Vector3d
    /// \param[out] _pt A msgs::Vector3d pointer
    /// \param[in] _v An ignition::math::Vector3d reference
    IGNITION_MSGS_VISIBLE
    void Set(msgs::Vector3d *_pt, const ignition::math::Vector3d &_v);

    /// \brief Set a msgs::Vector2d from an ignition::math::Vector2d
    /// \param[out] _pt A msgs::Vector2d pointer
    /// \param[in] _v An ignition::math::Vector2d reference
    IGNITION_MSGS_VISIBLE
    void Set(msgs::Vector2d *_pt, const ignition::math::Vector2d &_v);

    /// \brief Set a msgs::Quaternion from an ignition::math::Quaterniond
    /// \param[out] _q A msgs::Quaternion pointer
    /// \param[in] _v An ignition::math::Quaterniond reference
    IGNITION_MSGS_VISIBLE
    void Set(msgs::Quaternion *_q, const ignition::math::Quaterniond &_v);

    /// \brief Set a msgs::Pose from an ignition::math::Pose3d
    /// \param[out] _p A msgs::Pose pointer
    /// \param[in] _v An ignition::math::Pose3d reference
    IGNITION_MSGS_VISIBLE
    void Set(msgs::Pose *_p, const ignition::math::Pose3d &_v);

    /// \brief Set a msgs::Plane from an ignition::math::Planed
    /// \param[out] _p A msgs::Plane pointer
    /// \param[in] _v An ignition::math::Planed reference
    IGNITION_MSGS_VISIBLE
    void Set(msgs::PlaneGeom *_p, const ignition::math::Planed &_v);
  }
}
#endif
