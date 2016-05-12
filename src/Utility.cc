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
#include "ignition/msgs/Utility.hh"

namespace ignition
{
  namespace msgs
  {
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
      return ignition::math::Pose3d(Convert(_p.position()),
          Convert(_p.orientation()));
    }

    /////////////////////////////////////////////
    ignition::math::Planed Convert(const msgs::PlaneGeom &_p)
    {
      return ignition::math::Planed(Convert(_p.normal()),
          ignition::math::Vector2d(_p.size().x(), _p.size().y()),
          _p.d());
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
    msgs::PlaneGeom Convert(const ignition::math::Planed &_p)
    {
      msgs::PlaneGeom result;
      result.mutable_normal()->CopyFrom(Convert(_p.Normal()));
      result.mutable_size()->set_x(_p.Size().X());
      result.mutable_size()->set_y(_p.Size().Y());
      result.set_d(_p.Offset());
      return result;
    }

//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const double _d)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::DOUBLE);
//      result.set_double_value(_d);
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const int _i)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::INT32);
//      result.set_int_value(_i);
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const std::string &_s)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::STRING);
//      result.set_string_value(_s);
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const char *_s)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::STRING);
//      result.set_string_value(std::string(_s));
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const bool _b)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::BOOLEAN);
//      result.set_bool_value(_b);
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const ignition::math::Vector3d &_v)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::VECTOR3D);
//      result.mutable_vector3d_value()->CopyFrom(Convert(_v));
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const ignition::math::Pose3d &_p)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::POSE3D);
//      result.mutable_pose3d_value()->CopyFrom(Convert(_p));
//      return result;
//    }
//
//    /////////////////////////////////////////////////
//    ignition::msgs::Any ConvertAny(const ignition::math::Quaterniond &_q)
//    {
//      ignition::msgs::Any result;
//      result.set_type(ignition::msgs::Any::QUATERNIOND);
//      result.mutable_quaternion_value()->CopyFrom(Convert(_q));
//      return result;
//    }

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
  }
}
