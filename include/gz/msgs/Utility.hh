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
#ifndef GZ_MSGS_UTILITY_HH_
#define GZ_MSGS_UTILITY_HH_

#include <string>
#include <utility>
#include <vector>

#include <gz/math/AxisAlignedBox.hh>
#include <gz/math/Color.hh>
#include <gz/math/Inertial.hh>
#include <gz/math/Pose3.hh>
#include <gz/math/Plane.hh>
#include <gz/math/SphericalCoordinates.hh>
#include <gz/math/Vector3.hh>

#include "gz/msgs/config.hh"
#include "gz/msgs/Export.hh"
#include "gz/msgs/MessageTypes.hh"

/// \file Utility.hh
/// \brief Utility functions that support conversion between message type
/// and Gazebo Math types.

namespace gz
{
  namespace msgs
  {
    // Inline bracket to help doxygen filtering.
    inline namespace GZ_MSGS_VERSION_NAMESPACE {
    //
    /// \brief Convert a msgs::Vector3d to a gz::math::Vector
    /// \param[in] _v The vector to convert
    /// \return A gz::math::Vector3d object
    GZ_MSGS_VISIBLE
    gz::math::Vector3d Convert(const msgs::Vector3d &_v);

    /// \brief Convert a msgs::Vector2d to a gz::math::Vector2d
    /// \param[in] _v The vector2 to convert
    /// \return A gz::math::Vector2d object
    GZ_MSGS_VISIBLE
    gz::math::Vector2d Convert(const msgs::Vector2d &_v);

    /// \brief Convert a msgs::Quaternion to a gz::math::Quaterniond
    /// \param[in] _q The quaternion to convert
    /// \return A gz::math::Quaterniond object
    GZ_MSGS_VISIBLE
    gz::math::Quaterniond Convert(const msgs::Quaternion &_q);

    /// \brief Convert a msgs::Pose to a gz::math::Pose3d
    /// \param[in] _p The pose to convert
    /// \return A gz::math::Pose3d object
    GZ_MSGS_VISIBLE
    gz::math::Pose3d Convert(const msgs::Pose &_p);

    /// \brief Convert a msgs::Color to a math::Color
    /// \param[in] _c The color to convert
    /// \return A math::Color object
    GZ_MSGS_VISIBLE
    math::Color Convert(const msgs::Color &_c);

    /// \brief Convert a msgs::PlaneGeom to a gz::math::Planed
    /// \param[in] _p The plane to convert
    /// \return A gz::math::Planed object
    GZ_MSGS_VISIBLE
    gz::math::Planed Convert(const msgs::PlaneGeom &_p);

    /// \brief Convert a msgs::Inertial to a gz::math::Inertiald
    /// \param[in] _i The inertial to convert
    /// \return A gz::math::Inertiald object
    GZ_MSGS_VISIBLE
    math::Inertiald Convert(const msgs::Inertial &_i);

    /// \brief Convert a msgs::SphericalCoordinates to an
    /// gz::math::SphericalCoordinates
    /// \param[in] _coord The spherical coordinates to convert
    /// \return A gz::math::SphericalCoordinates object
    GZ_MSGS_VISIBLE
    math::SphericalCoordinates Convert(
        const msgs::SphericalCoordinates &_coord);

    /// \brief Convert a msgs::SphericalCoordinatesType to an
    /// gz::math::SphericalCoordinates::CoordinateTpye
    /// \param[in] _sc The spherical coordinate type to convert
    /// \return A gz::math::SphericalCoordinatesType object
    GZ_MSGS_VISIBLE
    math::SphericalCoordinates::CoordinateType Convert(
      const msgs::SphericalCoordinatesType &_sc);

    /// \brief Convert a msgs::AxisAlignedBox to an
    /// gz::math::AxisAlignedBox
    /// \param[in] _b The axis aligned box to convert
    /// \return A gz::math::AxisAlignedBox object
    GZ_MSGS_VISIBLE
    math::AxisAlignedBox Convert(const msgs::AxisAlignedBox &_b);

    /// \brief Convert gz::math::AxisAlignedBox to
    /// msgs::AxisAlignedBox.
    /// \param[in] _b The axis aligned box to convert
    /// \return A gz::math::AxisAlignedBox object
    GZ_MSGS_VISIBLE
    msgs::AxisAlignedBox Convert(const math::AxisAlignedBox &_b);

    /// \brief Convert a msgs::StringMsg to an std::string
    /// \param[in] _m The message to convert
    /// \return An std::string object
    GZ_MSGS_VISIBLE
    std::string Convert(const msgs::StringMsg &_m);

    /// \brief Convert a msgs::Boolean to a bool
    /// \param[in] _m The message to convert
    /// \return An bool object
    GZ_MSGS_VISIBLE
    bool Convert(const msgs::Boolean &_m);

    /// \brief Convert a msgs::Int32 to an int32_t
    /// \param[in] _m The message to convert
    /// \return An int32_t object
    GZ_MSGS_VISIBLE
    int32_t Convert(const msgs::Int32 &_m);

    /// \brief Convert a msgs::UInt32 to a uint32_t
    /// \param[in] _m The message to convert
    /// \return An uint32_t object
    GZ_MSGS_VISIBLE
    uint32_t Convert(const msgs::UInt32 &_m);

    /// \brief Convert a msgs::Int64 to an int64_t
    /// \param[in] _m The message to convert
    /// \return An int64_t object
    GZ_MSGS_VISIBLE
    int64_t Convert(const msgs::Int64 &_m);

    /// \brief Convert a msgs::UInt64 to a uint64_t
    /// \param[in] _m The message to convert
    /// \return An uint64_t object
    GZ_MSGS_VISIBLE
    uint64_t Convert(const msgs::UInt64 &_m);

    /// \brief Convert a msgs::Double to a double
    /// \param[in] _m The message to convert
    /// \return An double object
    GZ_MSGS_VISIBLE
    double Convert(const msgs::Double &_m);

    /// \brief Convert a msgs::Float to a float
    /// \param[in] _m The message to convert
    /// \return An float object
    GZ_MSGS_VISIBLE
    float Convert(const msgs::Float &_m);

    /// \brief Convert a msgs::Time to a std::chrono::steady_clock::duration
    /// \param[in] _time The message to convert
    /// \return A std::chrono::steady_clock::duration object
    GZ_MSGS_VISIBLE
    std::chrono::steady_clock::duration Convert(const msgs::Time &_time);

    /// \brief Convert a gz::math::Vector3d to a msgs::Vector3d
    /// \param[in] _v The vector to convert
    /// \return A msgs::Vector3d object
    GZ_MSGS_VISIBLE
    msgs::Vector3d Convert(const gz::math::Vector3d &_v);

    /// \brief Convert a gz::math::Vector2d to a msgs::Vector2d
    /// \param[in] _v The vector to convert
    /// \return A msgs::Vector2d object
    GZ_MSGS_VISIBLE
    msgs::Vector2d Convert(const gz::math::Vector2d &_v);

    /// \brief Convert a gz::math::Quaterniond to a msgs::Quaternion
    /// \param[in] _q The quaternion to convert
    /// \return A msgs::Quaternion object
    GZ_MSGS_VISIBLE
    msgs::Quaternion Convert(const gz::math::Quaterniond &_q);

    /// \brief Convert a gz::math::Pose3d to a msgs::Pose
    /// \param[in] _p The pose to convert
    /// \return A msgs::Pose object
    GZ_MSGS_VISIBLE
    msgs::Pose Convert(const gz::math::Pose3d &_p);

    /// \brief Convert a math::Color to a msgs::Color
    /// \param[in] _c The color to convert
    /// \return A msgs::Color object
    GZ_MSGS_VISIBLE
    msgs::Color Convert(const math::Color &_c);

    /// \brief Convert an math::Inertiald to a msgs::Inertial
    /// \param[in] _i The Inertiald to convert
    /// \return A msgs::Inertial object
    GZ_MSGS_VISIBLE
    msgs::Inertial Convert(const math::Inertiald &_i);

    /// \brief Convert an math::MassMatrix3d to a msgs::Inertial
    /// \param[in] _m The MassMatrix3d to convert
    /// \return A msgs::Inertial object
    GZ_MSGS_VISIBLE
    msgs::Inertial Convert(const math::MassMatrix3d &_m);

    /// \brief Convert an math::SphericalCoordinates to a
    /// msgs::SphericalCoordinates
    /// \param[in] _coord The SphericalCoordinates to convert
    /// \return A msgs::SphericalCoordinates object
    GZ_MSGS_VISIBLE
    msgs::SphericalCoordinates Convert(
        const math::SphericalCoordinates &_coord);

    /// \brief Convert a gz::math::SphericalCoordinates::CoordinateType
    /// to a msgs::SphericalCoordinatesType
    /// \param[in] _coord The spherical coordinates to convert
    /// \return A gz::msgs::SphericalCoordinatesType object
    GZ_MSGS_VISIBLE
    msgs::SphericalCoordinatesType ConvertCoord(
      const math::SphericalCoordinates::CoordinateType &_coord);

    /// \brief Convert a gz::math::Planed to a msgs::PlaneGeom
    /// \param[in] _p The plane to convert
    /// \return A msgs::PlaneGeom object
    GZ_MSGS_VISIBLE
    msgs::PlaneGeom Convert(const gz::math::Planed &_p);

    /// \brief Convert an std::string to a msgs::StringMsg
    /// \param[in] _s The string to convert
    /// \return A msgs::StringMsg object
    GZ_MSGS_VISIBLE
    msgs::StringMsg Convert(const std::string &_s);

    /// \brief Convert a bool to a msgs::Boolean
    /// \param[in] _b The bool to convert
    /// \return A msgs::Boolean object
    GZ_MSGS_VISIBLE
    msgs::Boolean Convert(const bool &_b);

    /// \brief Convert an int32_t to a msgs::Int32
    /// \param[in] _i The int32_t to convert
    /// \return A msgs::Int32 object
    GZ_MSGS_VISIBLE
    msgs::Int32 Convert(const int32_t &_i);

    /// \brief Convert a uint32_t to a msgs::UInt32
    /// \param[in] _u The uint32_t to convert
    /// \return A msgs::UInt32 object
    GZ_MSGS_VISIBLE
    msgs::UInt32 Convert(const uint32_t &_u);

    /// \brief Convert an int64_t to a msgs::Int64
    /// \param[in] _i The int64_t to convert
    /// \return A msgs::Int64 object
    GZ_MSGS_VISIBLE
    msgs::Int64 Convert(const int64_t &_i);

    /// \brief Convert a uint64_t to a msgs::UInt64
    /// \param[in] _u The uint64_t to convert
    /// \return A msgs::UInt64 object
    GZ_MSGS_VISIBLE
    msgs::UInt64 Convert(const uint64_t &_u);

    /// \brief Convert a double to a msgs::Double
    /// \param[in] _d The double to convert
    /// \return A msgs::Double object
    GZ_MSGS_VISIBLE
    msgs::Double Convert(const double &_d);

    /// \brief Convert a float to a msgs::Float
    /// \param[in] _f The float to convert
    /// \return A msgs::Float object
    GZ_MSGS_VISIBLE
    msgs::Float Convert(const float &_f);

    /// \brief Convert a std::chrono::steady_clock::duration to a msgs::Time
    /// \param[in] _time_point The std::chrono::system_clock::duration to
    /// convert
    /// \return A msgs::Time object
    GZ_MSGS_VISIBLE
    msgs::Time Convert(
      const std::chrono::steady_clock::duration &_time_point);

    /// \brief Convert a string to a msgs::Joint::Type enum.
    /// \param[in] _str Joint type string.
    /// \return A msgs::Joint::Type enum. Defaults to REVOLUTE
    /// if _str is unrecognized.
    GZ_MSGS_VISIBLE
    msgs::Joint::Type ConvertJointType(const std::string &_str);

    /// \brief Convert a msgs::Joint::Type to a string.
    /// \param[in] _type A msgs::Joint::Type enum.
    /// \return Joint type string. Returns "unknown" if
    /// _type is unrecognized.
    GZ_MSGS_VISIBLE
    std::string ConvertJointType(const msgs::Joint::Type &_type);

    /// \brief Convert a string to a msgs::Geometry::Type enum.
    /// \param[in] _str Geometry type string.
    /// \return A msgs::Geometry::Type enum.
    GZ_MSGS_VISIBLE
    msgs::Geometry::Type ConvertGeometryType(const std::string &_str);

    /// \brief Convert a msgs::Geometry::Type to a string.
    /// \param[in] _type A msgs::Geometry::Type enum.
    /// \return Geometry type string.
    GZ_MSGS_VISIBLE
    std::string ConvertGeometryType(const msgs::Geometry::Type _type);

    /// \brief Convert a string to a msgs::PixelFormatType enum.
    /// \param[in] _str PixelFormatType string.
    /// \return A msgs::PixelFormatType enum.
    GZ_MSGS_VISIBLE
    msgs::PixelFormatType ConvertPixelFormatType(const std::string &_str);

    /// \brief Convert a PixelFormatType to a string. This can be used for
    /// debugging purposes.
    // \param[in] _t PixelFormatType enum value.
    /// \return String version of PixelFormatType.
    GZ_MSGS_VISIBLE
    std::string ConvertPixelFormatType(const msgs::PixelFormatType &_t);

    /// \brief Convert a string to a msgs::Material::ShaderType enum.
    /// \param[in] _str Shader type string.
    /// \return A msgs::Material::ShaderType enum. Defaults to VERTEX
    /// if _str is unrecognized.
    GZ_MSGS_VISIBLE
    msgs::Material::ShaderType ConvertShaderType(const std::string &_str);

    /// \brief Convert a msgs::ShaderType to a string.
    /// \param[in] _type A msgs::ShaderType enum.
    /// \return Shader type string. Returns "unknown" if
    /// _type is unrecognized.
    GZ_MSGS_VISIBLE
    std::string ConvertShaderType(const msgs::Material::ShaderType &_type);

    /// \brief Set a msgs::Vector3d from a gz::math::Vector3d
    /// \param[out] _pt A msgs::Vector3d pointer
    /// \param[in] _v A gz::math::Vector3d reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Vector3d *_pt, const gz::math::Vector3d &_v);

    /// \brief Set a msgs::Vector2d from a gz::math::Vector2d
    /// \param[out] _pt A msgs::Vector2d pointer
    /// \param[in] _v A gz::math::Vector2d reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Vector2d *_pt, const gz::math::Vector2d &_v);

    /// \brief Set a msgs::Quaternion from a gz::math::Quaterniond
    /// \param[out] _q A msgs::Quaternion pointer
    /// \param[in] _v A gz::math::Quaterniond reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Quaternion *_q, const gz::math::Quaterniond &_v);

    /// \brief Set a msgs::Pose from a gz::math::Pose3d
    /// \param[out] _p A msgs::Pose pointer
    /// \param[in] _v A gz::math::Pose3d reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Pose *_p, const gz::math::Pose3d &_v);

    /// \brief Set a msgs::Color from a math::Color
    /// \param[out] _c A msgs::Color pointer
    /// \param[in] _v A math::Color reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Color *_c, const math::Color &_v);

    /// \brief Set a msgs::Inertial from an math::Inertiald
    /// \param[out] _i A msgs::Inertial pointer
    /// \param[in] _m An math::Inertiald reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Inertial *_i, const math::Inertiald &_m);

    /// \brief Set a msgs::Inertial from an math::MassMatrix3d
    /// \param[out] _i A msgs::Inertial pointer
    /// \param[in] _m An math::MassMatrix3d reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Inertial *_i, const math::MassMatrix3d &_m);

    /// \brief Set a msgs::SphericalCoordinates from a
    /// math::SphericalCoordinates
    /// \param[out] _sc A msgs::SphericalCoordinates pointer
    /// \param[in] _m An math::SphericalCoordinates reference
    GZ_MSGS_VISIBLE
    void Set(msgs::SphericalCoordinates *_sc,
        const math::SphericalCoordinates &_m);

    /// \brief Set a msgs::Plane from a gz::math::Planed
    /// \param[out] _p A msgs::Plane pointer
    /// \param[in] _v A gz::math::Planed reference
    GZ_MSGS_VISIBLE
    void Set(msgs::PlaneGeom *_p, const gz::math::Planed &_v);

    /// \brief Set a msgs::StringMsg from an std::string
    /// \param[out] _p A msgs::StringMsg pointer
    /// \param[in] _v An std::string reference
    GZ_MSGS_VISIBLE
    void Set(msgs::StringMsg *_p, const std::string &_v);

    /// \brief Set a msgs::Boolean from a bool
    /// \param[out] _p A msgs::Boolean pointer
    /// \param[in] _v An bool reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Boolean *_p, const bool &_v);

    /// \brief Set a msgs::Int32 from an int32_t
    /// \param[out] _p A msgs::Int32 pointer
    /// \param[in] _v An int32_t reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Int32 *_p, const int32_t &_v);

    /// \brief Set a msgs::UInt32 from a uint32_t
    /// \param[out] _p A msgs::UInt32 pointer
    /// \param[in] _v An uint32_t reference
    GZ_MSGS_VISIBLE
    void Set(msgs::UInt32 *_p, const uint32_t &_v);

    /// \brief Set a msgs::Int64 from an int64_t
    /// \param[out] _p A msgs::Int64 pointer
    /// \param[in] _v An int64_t reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Int64 *_p, const int64_t &_v);

    /// \brief Set a msgs::UInt64 from an uint64_t
    /// \param[out] _p A msgs::UInt64 pointer
    /// \param[in] _v An uint64_t reference
    GZ_MSGS_VISIBLE
    void Set(msgs::UInt64 *_p, const uint64_t &_v);

    /// \brief Set a msgs::Double from a double
    /// \param[out] _p A msgs::Double pointer
    /// \param[in] _v An double reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Double *_p, const double &_v);

    /// \brief Set a msgs::Float from a float
    /// \param[out] _p A msgs::Float pointer
    /// \param[in] _v An float reference
    GZ_MSGS_VISIBLE
    void Set(msgs::Float *_p, const float &_v);

    /// \brief Set a msgs::AxisAlignedBox from a math::AxisAlignedBox
    /// \param[out] _b A msgs::AxisAlignedBox pointer
    /// \param[in] _v An math::AxisAlignedBox reference
    GZ_MSGS_VISIBLE
    void Set(msgs::AxisAlignedBox *_b, const math::AxisAlignedBox &_v);

    /// \brief This function will set the header and field members of
    /// a PointCloudPacked message. This will clear existing values in the
    /// PointCloudPacked field and header.
    /// \param[out] _msg The message to initialize.
    /// \param[in] _frameId Name of the "frame_id". This will be stored as
    /// key = "frame_id", value = _frameId in the message header.
    /// \param[in] _memoryAligned If true, then each pair in the _fields
    /// vector will be aligned at word (sizeof(size_t)) boundaries.
    /// Additionally, the `point_step` of the _msg will be set to the
    /// nearest word boundary.
    /// \param[in] _fields The fields to add to the message. The following
    /// strings are reserved, and will generate a set of fields
    /// automatically.
    ///
    ///   * "xyz" : This will add the "x", "y", and "z" fields.
    GZ_MSGS_VISIBLE
    void InitPointCloudPacked(msgs::PointCloudPacked &_msg,
        const std::string &_frameId, bool _memoryAligned,
        const std::vector<std::pair<std::string,
        msgs::PointCloudPacked::Field::DataType>> &_fields);

    /// \brief Convert a Discovery::Type to a string. This can be used for
    /// debugging purposes.
    // \param[in] _t Type of the discovery message.
    /// \return String version of Discovery::Type.
    GZ_MSGS_VISIBLE
    std::string ToString(const msgs::Discovery::Type &_t);

    /// \brief Convert the contents of a model.config file, in the form of
    /// an XML string, to a FuelMetadata message.
    ///
    /// Only the latest versioned model is added to the meta data message.
    ///
    /// The `<depend>` and `<version>` tags are ignored.
    ///
    /// \param[in] _modelConfigStr A string containing XML data that matches
    /// the model.config format.
    /// \param[out] _meta The message that receives the converted data.
    /// \return True if the conversion was successful.
    GZ_MSGS_VISIBLE
    bool ConvertFuelMetadata(const std::string &_modelConfigStr,
                             msgs::FuelMetadata &_meta);

    /// \brief Convert a FuelMetadata message to a string containing XML
    /// data that matches the model.config format.
    ///
    /// The model.config format contains only a subset of the information in
    /// a metadata message. The extra information in the metadata message is
    /// discarded.
    ///
    /// \param[in] _meta The FuelMetadata message to convert.
    /// \param[out] _modelConfigStr XML string containing the converted
    /// message data.
    /// \return True if the conversion was successful.
    GZ_MSGS_VISIBLE
    bool ConvertFuelMetadata(const msgs::FuelMetadata &_meta,
                             std::string &_modelConfigStr);
    }
  }
}
#endif
