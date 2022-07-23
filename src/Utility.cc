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
#include <tinyxml2.h>
#include <functional>
#include <sstream>
#include <ignition/math/Helpers.hh>
#include <ignition/math/SemanticVersion.hh>
#include "ignition/msgs/Utility.hh"

#ifdef _WIN32
  const auto &ignstrtok = strtok_s;
#else
  const auto &ignstrtok = strtok_r;
#endif


namespace ignition
{
  namespace msgs
  {
    // Inline bracket to help doxygen filtering.
    inline namespace IGNITION_MSGS_VERSION_NAMESPACE {
    /// \brief Left and right trim a string. This was copied from ignition
    /// common, ign-common/Util.hh, to avoid adding another dependency.
    /// Remove this function if ign-common ever becomes a dependency.
    /// \param[in] _s String to trim
    /// \return Trimmed string
    std::string trimmed(std::string _s)
    {
      // Left trim
      _s.erase(_s.begin(), std::find_if(_s.begin(), _s.end(),
            [](int c) {return !std::isspace(c);}));

      // Right trim
      _s.erase(std::find_if(_s.rbegin(), _s.rend(),
            [](int c) {return !std::isspace(c);}).base(), _s.end());

      return _s;
    }

    /////////////////////////////////////////////
    ignition::math::Vector3d Convert(const msgs::Vector3d &_v)
    {
      return ignition::math::Vector3d(_v.x(), _v.y(), _v.z());
    }

    /////////////////////////////////////////////
    ignition::math::Vector2d Convert(const msgs::Vector2d &_v)
    {
      return ignition::math::Vector2d(_v.x(), _v.y());
    }

    /////////////////////////////////////////////
    ignition::math::Quaterniond Convert(const msgs::Quaternion &_q)
    {
      return ignition::math::Quaterniond(_q.w(), _q.x(), _q.y(), _q.z());
    }

    /////////////////////////////////////////////
    ignition::math::Pose3d Convert(const msgs::Pose &_p)
    {
      ignition::math::Pose3d result;

      if (_p.has_position())
       result.Pos() = Convert(_p.position());
      if (_p.has_orientation())
       result.Rot() = Convert(_p.orientation());

      return result;
    }

    /////////////////////////////////////////////
    math::Inertiald Convert(const msgs::Inertial &_i)
    {
      auto pose = msgs::Convert(_i.pose());
      return math::Inertiald(
        math::MassMatrix3d(
          _i.mass(),
          math::Vector3d(_i.ixx(), _i.iyy(), _i.izz()),
          math::Vector3d(_i.ixy(), _i.ixz(), _i.iyz())),
        pose);
    }

    /////////////////////////////////////////////
    math::AxisAlignedBox Convert(const msgs::AxisAlignedBox &_b)
    {
      return math::AxisAlignedBox(msgs::Convert(_b.min_corner()),
                                  msgs::Convert(_b.max_corner()));
    }

    /////////////////////////////////////////////
    msgs::AxisAlignedBox Convert(const math::AxisAlignedBox &_b)
    {
      msgs::AxisAlignedBox result;
      msgs::Set(result.mutable_min_corner(), _b.Min());
      msgs::Set(result.mutable_max_corner(), _b.Max());
      return result;
    }

    /////////////////////////////////////////////
    void Set(msgs::AxisAlignedBox *_b, const math::AxisAlignedBox &_v)
    {
      msgs::Set(_b->mutable_min_corner(), _v.Min());
      msgs::Set(_b->mutable_max_corner(), _v.Max());
    }

    /////////////////////////////////////////////
    math::Color Convert(const msgs::Color &_c)
    {
      return math::Color(_c.r(), _c.g(), _c.b(), _c.a());
    }

    /////////////////////////////////////////////
    ignition::math::Planed Convert(const msgs::PlaneGeom &_p)
    {
      return ignition::math::Planed(Convert(_p.normal()),
          ignition::math::Vector2d(_p.size().x(), _p.size().y()),
          _p.d());
    }

    /////////////////////////////////////////////
    std::string Convert(const msgs::StringMsg &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    bool Convert(const msgs::Boolean &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    int32_t Convert(const msgs::Int32 &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    uint32_t Convert(const msgs::UInt32 &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    int64_t Convert(const msgs::Int64 &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    uint64_t Convert(const msgs::UInt64 &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    double Convert(const msgs::Double &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////
    float Convert(const msgs::Float &_m)
    {
      return _m.data();
    }

    /////////////////////////////////////////////////
    msgs::Vector3d Convert(const ignition::math::Vector3d &_v)
    {
      msgs::Vector3d result;
      result.set_x(_v.X());
      result.set_y(_v.Y());
      result.set_z(_v.Z());
      return result;
    }

    /////////////////////////////////////////////////
    msgs::Vector2d Convert(const ignition::math::Vector2d &_v)
    {
      msgs::Vector2d result;
      result.set_x(_v.X());
      result.set_y(_v.Y());
      return result;
    }

    /////////////////////////////////////////////
    msgs::Quaternion Convert(const ignition::math::Quaterniond &_q)
    {
      msgs::Quaternion result;
      result.set_x(_q.X());
      result.set_y(_q.Y());
      result.set_z(_q.Z());
      result.set_w(_q.W());
      return result;
    }

    /////////////////////////////////////////////
    msgs::Pose Convert(const ignition::math::Pose3d &_p)
    {
      msgs::Pose result;
      result.mutable_position()->CopyFrom(Convert(_p.Pos()));
      result.mutable_orientation()->CopyFrom(Convert(_p.Rot()));
      return result;
    }

    /////////////////////////////////////////////
    msgs::Color Convert(const math::Color &_c)
    {
      msgs::Color result;
      result.set_r(_c.R());
      result.set_g(_c.G());
      result.set_b(_c.B());
      result.set_a(_c.A());
      return result;
    }

    /////////////////////////////////////////////
    msgs::Inertial Convert(const math::Inertiald &_i)
    {
      msgs::Inertial result;
      msgs::Set(&result, _i);
      return result;
    }

    /////////////////////////////////////////////
    msgs::Inertial Convert(const math::MassMatrix3d &_m)
    {
      msgs::Inertial result;
      msgs::Set(&result, _m);
      return result;
    }

    /////////////////////////////////////////////
    msgs::PlaneGeom Convert(const ignition::math::Planed &_p)
    {
      msgs::PlaneGeom result;
      result.mutable_normal()->CopyFrom(Convert(_p.Normal()));
      result.mutable_size()->set_x(_p.Size().X());
      result.mutable_size()->set_y(_p.Size().Y());
      result.set_d(_p.Offset());
      return result;
    }

    /////////////////////////////////////////////
    msgs::StringMsg Convert(const std::string &_s)
    {
      msgs::StringMsg result;
      result.set_data(_s);
      return result;
    }

    /////////////////////////////////////////////
    msgs::Boolean Convert(const bool &_b)
    {
      msgs::Boolean result;
      result.set_data(_b);
      return result;
    }

    /////////////////////////////////////////////
    msgs::Int32 Convert(const int32_t &_i)
    {
      msgs::Int32 result;
      result.set_data(_i);
      return result;
    }

    /////////////////////////////////////////////
    msgs::UInt32 Convert(const uint32_t &_u)
    {
      msgs::UInt32 result;
      result.set_data(_u);
      return result;
    }

    /////////////////////////////////////////////
    msgs::Int64 Convert(const int64_t &_i)
    {
      msgs::Int64 result;
      result.set_data(_i);
      return result;
    }

    /////////////////////////////////////////////
    msgs::UInt64 Convert(const uint64_t &_u)
    {
      msgs::UInt64 result;
      result.set_data(_u);
      return result;
    }


    /////////////////////////////////////////////
    msgs::Double Convert(const double &_d)
    {
      msgs::Double result;
      result.set_data(_d);
      return result;
    }

    /////////////////////////////////////////////
    msgs::Float Convert(const float &_f)
    {
      msgs::Float result;
      result.set_data(_f);
      return result;
    }

    /////////////////////////////////////////////
    void Set(msgs::Vector3d *_pt, const ignition::math::Vector3d &_v)
    {
      _pt->set_x(_v.X());
      _pt->set_y(_v.Y());
      _pt->set_z(_v.Z());
    }

    /////////////////////////////////////////////
    void Set(msgs::Vector2d *_pt, const ignition::math::Vector2d &_v)
    {
      _pt->set_x(_v.X());
      _pt->set_y(_v.Y());
    }

    /////////////////////////////////////////////
    void Set(msgs::Quaternion *_q, const ignition::math::Quaterniond &_v)
    {
      _q->set_x(_v.X());
      _q->set_y(_v.Y());
      _q->set_z(_v.Z());
      _q->set_w(_v.W());
    }

    /////////////////////////////////////////////
    void Set(msgs::Pose *_p, const ignition::math::Pose3d &_v)
    {
      Set(_p->mutable_position(), _v.Pos());
      Set(_p->mutable_orientation(), _v.Rot());
    }

    /////////////////////////////////////////////////
    void Set(msgs::PlaneGeom *_p, const ignition::math::Planed &_v)
    {
      Set(_p->mutable_normal(), _v.Normal());
      _p->mutable_size()->set_x(_v.Size().X());
      _p->mutable_size()->set_y(_v.Size().Y());
      _p->set_d(_v.Offset());
    }

    /////////////////////////////////////////////
    void Set(msgs::Color *_c, const math::Color &_v)
    {
      _c->set_r(_v.R());
      _c->set_g(_v.G());
      _c->set_b(_v.B());
      _c->set_a(_v.A());
    }

    /////////////////////////////////////////////////
    void Set(msgs::Inertial *_i, const math::MassMatrix3d &_m)
    {
      _i->set_mass(_m.Mass());
      _i->set_ixx(_m.Ixx());
      _i->set_iyy(_m.Iyy());
      _i->set_izz(_m.Izz());
      _i->set_ixy(_m.Ixy());
      _i->set_ixz(_m.Ixz());
      _i->set_iyz(_m.Iyz());
    }

    /////////////////////////////////////////////////
    void Set(msgs::Inertial *_i, const math::Inertiald &_m)
    {
      msgs::Set(_i, _m.MassMatrix());
      msgs::Set(_i->mutable_pose(), _m.Pose());
    }

    /////////////////////////////////////////////////
    void Set(msgs::StringMsg *_p, const std::string &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::Boolean *_p, const bool &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::Int32 *_p, const int32_t &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::UInt32 *_p, const uint32_t &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::Int64 *_p, const int64_t &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::UInt64 *_p, const uint64_t &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::Double *_p, const double &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////////
    void Set(msgs::Float *_p, const float &_v)
    {
      _p->set_data(_v);
    }

    /////////////////////////////////////////////
    msgs::Joint::Type ConvertJointType(const std::string &_str)
    {
      msgs::Joint::Type result = msgs::Joint::REVOLUTE;
      if (_str == "revolute")
      {
        result = msgs::Joint::REVOLUTE;
      }
      else if (_str == "revolute2")
      {
        result = msgs::Joint::REVOLUTE2;
      }
      else if (_str == "prismatic")
      {
        result = msgs::Joint::PRISMATIC;
      }
      else if (_str == "universal")
      {
        result = msgs::Joint::UNIVERSAL;
      }
      else if (_str == "ball")
      {
        result = msgs::Joint::BALL;
      }
      else if (_str == "screw")
      {
        result = msgs::Joint::SCREW;
      }
      else if (_str == "gearbox")
      {
        result = msgs::Joint::GEARBOX;
      }
      else if (_str == "fixed")
      {
        result = msgs::Joint::FIXED;
      }
      else
      {
        std::cerr << "Unrecognized JointType ["
                  << _str
                  << "], returning msgs::Joint::REVOLUTE"
                  << std::endl;
      }
      return result;
    }

    /////////////////////////////////////////////
    std::string ConvertJointType(const msgs::Joint::Type &_type)
    {
      std::string result;
      switch (_type)
      {
        case msgs::Joint::REVOLUTE:
        {
          result = "revolute";
          break;
        }
        case msgs::Joint::REVOLUTE2:
        {
          result = "revolute2";
          break;
        }
        case msgs::Joint::PRISMATIC:
        {
          result = "prismatic";
          break;
        }
        case msgs::Joint::UNIVERSAL:
        {
          result = "universal";
          break;
        }
        case msgs::Joint::BALL:
        {
          result = "ball";
          break;
        }
        case msgs::Joint::SCREW:
        {
          result = "screw";
          break;
        }
        case msgs::Joint::GEARBOX:
        {
          result = "gearbox";
          break;
        }
        case msgs::Joint::FIXED:
        {
          result = "fixed";
          break;
        }
        default:
        {
          result = "unknown";
          std::cerr << "Unrecognized JointType ["
                    << _type
                    << "], returning 'unknown'"
                    << std::endl;
          break;
        }
      }
      return result;
    }

    /////////////////////////////////////////////////
    msgs::Geometry::Type ConvertGeometryType(const std::string &_str)
    {
      msgs::Geometry::Type result = msgs::Geometry::BOX;
      if (_str == "box")
      {
        result = msgs::Geometry::BOX;
      }
      else if (_str == "cylinder")
      {
        result = msgs::Geometry::CYLINDER;
      }
      else if (_str == "sphere")
      {
        result = msgs::Geometry::SPHERE;
      }
      else if (_str == "plane")
      {
        result = msgs::Geometry::PLANE;
      }
      else if (_str == "image")
      {
        result = msgs::Geometry::IMAGE;
      }
      else if (_str == "heightmap")
      {
        result = msgs::Geometry::HEIGHTMAP;
      }
      else if (_str == "mesh")
      {
        result = msgs::Geometry::MESH;
      }
      else if (_str == "polyline")
      {
        result = msgs::Geometry::POLYLINE;
      }
      else
      {
        std::cerr << "Unrecognized Geometry::Type ["
                  << _str
                  << "], returning msgs::Geometry::BOX"
                  << std::endl;
      }

      return result;
    }

    /////////////////////////////////////////////////
    std::string ConvertGeometryType(const msgs::Geometry::Type _type)
    {
      std::string result;
      switch (_type)
      {
        case msgs::Geometry::BOX:
        {
          result = "box";
          break;
        }
        case msgs::Geometry::CYLINDER:
        {
          result = "cylinder";
          break;
        }
        case msgs::Geometry::SPHERE:
        {
          result = "sphere";
          break;
        }
        case msgs::Geometry::PLANE:
        {
          result = "plane";
          break;
        }
        case msgs::Geometry::IMAGE:
        {
          result = "image";
          break;
        }
        case msgs::Geometry::HEIGHTMAP:
        {
          result = "heightmap";
          break;
        }
        case msgs::Geometry::MESH:
        {
          result = "mesh";
          break;
        }
        case msgs::Geometry::POLYLINE:
        {
          result = "polyline";
          break;
        }
        default:
        {
          result = "unknown";
          std::cerr << "Unrecognized Geometry::Type ["
                    << _type
                    << "], returning 'unknown'"
                    << std::endl;
          break;
        }
      }
      return result;
    }

    /////////////////////////////////////////////////
    msgs::Material::ShaderType ConvertShaderType(const std::string &_str)
    {
      auto result = msgs::Material::VERTEX;
      if (_str == "vertex")
      {
        result = msgs::Material::VERTEX;
      }
      else if (_str == "pixel")
      {
        result = msgs::Material::PIXEL;
      }
      else if (_str == "normal_map_object_space")
      {
        result = msgs::Material::NORMAL_MAP_OBJECT_SPACE;
      }
      else if (_str == "normal_map_tangent_space")
      {
        result = msgs::Material::NORMAL_MAP_TANGENT_SPACE;
      }
      else
      {
        std::cerr << "Unrecognized Material::ShaderType ["
                  << _str
                  << "], returning msgs::Material::VERTEX"
                  << std::endl;
      }
      return result;
    }

    /////////////////////////////////////////////////
    std::string ConvertShaderType(const msgs::Material::ShaderType &_type)
    {
      std::string result;
      switch (_type)
      {
        case msgs::Material::VERTEX:
        {
          result = "vertex";
          break;
        }
        case msgs::Material::PIXEL:
        {
          result = "pixel";
          break;
        }
        case msgs::Material::NORMAL_MAP_OBJECT_SPACE:
        {
          result = "normal_map_object_space";
          break;
        }
        case msgs::Material::NORMAL_MAP_TANGENT_SPACE:
        {
          result = "normal_map_tangent_space";
          break;
        }
        default:
        {
          result = "unknown";
          std::cerr << "Unrecognized Material::ShaderType ["
                    << _type
                    << "], returning 'unknown'"
                    << std::endl;
          break;
        }
      }
      return result;
    }

    /////////////////////////////////////////////////
    void InitPointCloudPacked(msgs::PointCloudPacked &_msg,
        const std::string &_frameId, bool _memoryAligned,
        const std::vector<std::pair<std::string,
        msgs::PointCloudPacked::Field::DataType>> &_fields)
    {
      uint32_t offset = 0;

      // Helper function that will set a single field.
      std::function<void(const std::string &,
        msgs::PointCloudPacked::Field::DataType)> initPointCloudPackedHelper =
        [&](const std::string &_name,
           msgs::PointCloudPacked::Field::DataType _type) -> void
        {
          msgs::PointCloudPacked::Field *newField = _msg.add_field();
          newField->set_name(_name);
          newField->set_count(1);
          newField->set_datatype(_type);
          newField->set_offset(offset);
          switch (_type)
          {
            case msgs::PointCloudPacked::Field::INT8:
            case msgs::PointCloudPacked::Field::UINT8:
              offset += 1;
              break;
            case msgs::PointCloudPacked::Field::INT16:
            case msgs::PointCloudPacked::Field::UINT16:
              offset += 2;
              break;
            case msgs::PointCloudPacked::Field::INT32:
            case msgs::PointCloudPacked::Field::UINT32:
            case msgs::PointCloudPacked::Field::FLOAT32:
              offset += 4;
              break;
            case msgs::PointCloudPacked::Field::FLOAT64:
              offset += 8;
              break;
            // LCOV_EXCL_START
            default:
              std::cerr << "PointCloudPacked field datatype of ["
                << _type << "] is invalid.\n";
              break;
            // LCOV_EXCL_STOP
          }
        };

      // Set the frame
      _msg.mutable_header()->clear_data();
      msgs::Header::Map *frame = _msg.mutable_header()->add_data();
      frame->set_key("frame_id");
      frame->add_value(_frameId);

      _msg.clear_field();
      // Setup the point cloud message.
      for (const std::pair<std::string,
           msgs::PointCloudPacked::Field::DataType> &field : _fields)
      {
        if (field.first == "xyz")
        {
          initPointCloudPackedHelper("x", field.second);
          initPointCloudPackedHelper("y", field.second);
          initPointCloudPackedHelper("z", field.second);
        }
        else
        {
          initPointCloudPackedHelper(field.first, field.second);
        }

        // Memory align the field.
        if (_memoryAligned)
          offset = math::roundUpMultiple(offset, sizeof(size_t));
      }

      // Set the point_step
      if (_memoryAligned)
        _msg.set_point_step(math::roundUpMultiple(offset, sizeof(size_t)));
      else
        _msg.set_point_step(offset);
    }

    /////////////////////////////////////////////
    std::string ToString(const msgs::Discovery::Type &_t)
    {
      switch (_t)
      {
        default:
        case msgs::Discovery::UNINITIALIZED:
          return "UNINITIALIZED";
        case msgs::Discovery::ADVERTISE:
          return "ADVERTISE";
        case msgs::Discovery::SUBSCRIBE:
          return "SUBSCRIBE";
        case msgs::Discovery::UNADVERTISE:
          return "UNADVERTISE";
        case msgs::Discovery::HEARTBEAT:
          return "HEARTBEAT";
        case msgs::Discovery::BYE:
          return "BYE";
        case msgs::Discovery::NEW_CONNECTION:
          return "NEW_CONNECTION";
        case msgs::Discovery::END_CONNECTION:
          return "END_CONNECTION";
      };
    }

    /////////////////////////////////////////////
    msgs::PixelFormatType ConvertPixelFormatType(const std::string &_str)
    {
      if (_str == "L_INT8")
      {
        return msgs::PixelFormatType::L_INT8;
      }
      else if (_str == "L_INT16")
      {
        return msgs::PixelFormatType::L_INT16;
      }
      else if (_str == "RGB_INT8")
      {
        return msgs::PixelFormatType::RGB_INT8;
      }
      else if (_str == "RGBA_INT8")
      {
        return msgs::PixelFormatType::RGBA_INT8;
      }
      else if (_str == "BGRA_INT8")
      {
        return msgs::PixelFormatType::BGRA_INT8;
      }
      else if (_str == "RGB_INT16")
      {
        return msgs::PixelFormatType::RGB_INT16;
      }
      else if (_str == "RGB_INT32")
      {
        return msgs::PixelFormatType::RGB_INT32;
      }
      else if (_str == "BGR_INT8")
      {
        return msgs::PixelFormatType::BGR_INT8;
      }
      else if (_str == "BGR_INT16")
      {
        return msgs::PixelFormatType::BGR_INT16;
      }
      else if (_str == "BGR_INT32")
      {
        return msgs::PixelFormatType::BGR_INT32;
      }
      else if (_str == "R_FLOAT16")
      {
        return msgs::PixelFormatType::R_FLOAT16;
      }
      else if (_str == "RGB_FLOAT16")
      {
        return msgs::PixelFormatType::RGB_FLOAT16;
      }
      else if (_str == "R_FLOAT32")
      {
        return msgs::PixelFormatType::R_FLOAT32;
      }
      else if (_str == "RGB_FLOAT32")
      {
        return msgs::PixelFormatType::RGB_FLOAT32;
      }
      else if (_str == "BAYER_RGGB8")
      {
        return msgs::PixelFormatType::BAYER_RGGB8;
      }
      else if (_str == "BAYER_BGGR8")
      {
        return msgs::PixelFormatType::BAYER_BGGR8;
      }
      else if (_str == "BAYER_GBRG8")
      {
        return msgs::PixelFormatType::BAYER_GBRG8;
      }
      else if (_str == "BAYER_GRBG8")
      {
        return msgs::PixelFormatType::BAYER_GRBG8;
      }

      return msgs::PixelFormatType::UNKNOWN_PIXEL_FORMAT;
    }

    /////////////////////////////////////////////
    std::string ConvertPixelFormatType(const msgs::PixelFormatType &_t)
    {
      switch (_t)
      {
        default:
        case msgs::PixelFormatType::UNKNOWN_PIXEL_FORMAT:
          return "UNKNOWN_PIXEL_FORMAT";
        case msgs::PixelFormatType::L_INT8:
          return "L_INT8";
        case msgs::PixelFormatType::L_INT16:
          return "L_INT16";
        case msgs::PixelFormatType::RGB_INT8:
          return "RGB_INT8";
        case msgs::PixelFormatType::RGBA_INT8:
          return "RGBA_INT8";
        case msgs::PixelFormatType::BGRA_INT8:
          return "BGRA_INT8";
        case msgs::PixelFormatType::RGB_INT16:
          return "RGB_INT16";
        case msgs::PixelFormatType::RGB_INT32:
          return "RGB_INT32";
        case msgs::PixelFormatType::BGR_INT8:
          return "BGR_INT8";
        case msgs::PixelFormatType::BGR_INT16:
          return "BGR_INT16";
        case msgs::PixelFormatType::BGR_INT32:
          return "BGR_INT32";
        case msgs::PixelFormatType::R_FLOAT16:
          return "R_FLOAT16";
        case msgs::PixelFormatType::RGB_FLOAT16:
          return "RGB_FLOAT16";
        case msgs::PixelFormatType::R_FLOAT32:
          return "R_FLOAT32";
        case msgs::PixelFormatType::RGB_FLOAT32:
          return "RGB_FLOAT32";
        case msgs::PixelFormatType::BAYER_RGGB8:
          return "BAYER_RGGB8";
        case msgs::PixelFormatType::BAYER_BGGR8:
          return "BAYER_BGGR8";
        case msgs::PixelFormatType::BAYER_GBRG8:
          return "BAYER_GBRG8";
        case msgs::PixelFormatType::BAYER_GRBG8:
          return "BAYER_GRBG8";
      };
    }

    /////////////////////////////////////////////////
    bool ConvertFuelMetadata(const std::string &_modelConfigStr,
                             msgs::FuelMetadata &_meta)
    {
      ignition::msgs::FuelMetadata meta;

      // Load the model config into tinyxml
      tinyxml2::XMLDocument modelConfigDoc;
      if (modelConfigDoc.Parse(_modelConfigStr.c_str()) !=
          tinyxml2::XML_SUCCESS)
      {
        std::cerr << "Unable to parse model config XML string.\n";
        return false;
      }

      // Get the top level <model> or <world> element.
      tinyxml2::XMLElement *topElement = modelConfigDoc.FirstChildElement(
          "model");
      bool isModel = true;
      if (!topElement)
      {
        topElement = modelConfigDoc.FirstChildElement("world");
        if (!topElement)
        {
          std::cerr << "Model config string does not contain a "
                    << "<model> or <world> element\n";
          return false;
        }
        isModel = false;
      }

      // Read the name, which is a mandatory element.
      tinyxml2::XMLElement *elem = topElement->FirstChildElement("name");
      if (!elem || !elem->GetText())
      {
        std::cerr << "Model config string does not contain a <name> element\n";
        return false;
      }
      meta.set_name(trimmed(elem->GetText()));

      // Read the version, if present.
      elem = topElement->FirstChildElement("version");
      if (elem && elem->GetText())
      {
        auto version = std::stoi(trimmed(elem->GetText()));
        meta.set_version(version);
      }

      // Read the description, if present.
      elem = topElement->FirstChildElement("description");
      if (elem && elem->GetText())
        meta.set_description(trimmed(elem->GetText()));

      // Read the dependencies, if any.
      elem = topElement->FirstChildElement("depend");
      while (elem)
      {
        auto modelElem = elem->FirstChildElement("model");
        if (modelElem)
        {
          auto uriElem = modelElem->FirstChildElement("uri");
          if (uriElem)
          {
            auto dependency = meta.add_dependencies();
            dependency->set_uri(uriElem->GetText());
          }
        }
        elem = elem->NextSiblingElement("depend");
      }

      // Read the authors, if any.
      elem = topElement->FirstChildElement("author");
      while (elem)
      {
        ignition::msgs::FuelMetadata::Contact *author = meta.add_authors();
        // Get the author name and email
        if (elem->FirstChildElement("name") &&
            elem->FirstChildElement("name")->GetText())
        {
          author->set_name(trimmed(elem->FirstChildElement("name")->GetText()));
        }
        if (elem->FirstChildElement("email") &&
            elem->FirstChildElement("email")->GetText())
        {
          author->set_email(
              trimmed(elem->FirstChildElement("email")->GetText()));
        }

        elem = elem->NextSiblingElement("author");
      }

      // Get the most recent SDF file
      elem = topElement->FirstChildElement("sdf");
      math::SemanticVersion maxVer;
      while (elem)
      {
        if (elem->GetText() && elem->Attribute("version"))
        {
          std::string verStr = elem->Attribute("version");
          math::SemanticVersion ver(trimmed(verStr));
          if (ver > maxVer)
          {
            ignition::msgs::Version *verMsg;

            if (isModel)
            {
              meta.mutable_model()->mutable_file_format()->set_name("sdf");
              verMsg =
                meta.mutable_model()->mutable_file_format()->mutable_version();
              meta.mutable_model()->set_file(trimmed(elem->GetText()));
            }
            else
            {
              meta.mutable_world()->mutable_file_format()->set_name("sdf");
              verMsg =
                meta.mutable_world()->mutable_file_format()->mutable_version();
              meta.mutable_world()->set_file(trimmed(elem->GetText()));
            }

            verMsg->set_major(ver.Major());
            verMsg->set_minor(ver.Minor());
            verMsg->set_patch(ver.Patch());
            verMsg->set_prerelease(ver.Prerelease());
            verMsg->set_build(ver.Build());
          }
        }

        elem = elem->NextSiblingElement("sdf");
      }
      if (meta.model().file().empty() && meta.world().file().empty())
      {
        std::cerr << "Model config string does not contain an <sdf> element\n";
        return false;
      }

      _meta.CopyFrom(meta);
      return true;
    }

    /////////////////////////////////////////////////
    bool ConvertFuelMetadata(const msgs::FuelMetadata &_meta,
                             std::string &_modelConfigStr)
    {
      std::ostringstream out;

      // Output opening tag.
      if (_meta.has_model())
      {
        if (_meta.model().file_format().name() != "sdf")
        {
          std::cerr << "Model _metadata does not contain an SDF file.\n";
          return false;
        }

        out << "<?xml version='1.0'?>\n"
            << "  <model>\n"
            << "    <sdf version='"
            << _meta.model().file_format().version().major()
            << "." << _meta.model().file_format().version().minor() << "'>"
            << _meta.model().file() << "</sdf>\n";
      }
      else
      {
        if (_meta.world().file_format().name() != "sdf")
        {
          std::cerr << "World _metadata does not contain an SDF file.\n";
          return false;
        }

        out << "<?xml version='1.0'?>\n"
            << "  <world>\n"
            << "    <sdf version='"
            << _meta.world().file_format().version().major()
            << "." << _meta.world().file_format().version().minor() << "'>"
            << _meta.world().file() << "</sdf>\n";
      }

      out << "    <name>" << _meta.name() << "</name>\n"
          << "    <version>" << _meta.version() << "</version>\n"
          << "    <description>" << _meta.description() << "</description>\n";

      // Output author information.
      for (int i = 0; i < _meta.authors_size(); ++i)
      {
        out << "    <author>\n"
        << "      <name>" << _meta.authors(i).name() << "</name>\n"
        << "      <email>" << _meta.authors(i).email() << "</email>\n"
        << "    </author>\n";
      }

      // Output dependency information.
      for (int i = 0; i < _meta.dependencies_size(); ++i)
      {
        out << "    <depend>\n"
        << "      <model>\n"
        << "        <uri>" << _meta.dependencies(i).uri() << "</uri>\n"
        << "      </model>\n"
        << "    </depend>\n";
      }

      // Output closing tag.
      if (_meta.has_model())
        out << "  </model>\n";
      else
        out << "  </world>\n";

      _modelConfigStr = out.str();
      return true;
    }
  }
}
}
