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
      ignition::math::Pose3d result;

      if (_p.has_position())
       result.Pos() = Convert(_p.position());
      if (_p.has_orientation())
       result.Rot() = Convert(_p.orientation());

      return result;
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
