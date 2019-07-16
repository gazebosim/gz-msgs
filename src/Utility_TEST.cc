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

#include <gtest/gtest.h>
#include <limits>
#include <ignition/math/Helpers.hh>
#include "ignition/msgs/MessageTypes.hh"
#include "ignition/msgs/Utility.hh"

using namespace ignition;

/////////////////////////////////////////////////
TEST(UtilityTest, CovertMathVector3ToMsgs)
{
  msgs::Vector3d msg = msgs::Convert(math::Vector3d(1, 2, 3));
  EXPECT_DOUBLE_EQ(1, msg.x());
  EXPECT_DOUBLE_EQ(2, msg.y());
  EXPECT_DOUBLE_EQ(3, msg.z());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMsgsVector3dToMath)
{
  msgs::Vector3d msg = msgs::Convert(math::Vector3d(1, 2, 3));
  math::Vector3d v = msgs::Convert(msg);
  EXPECT_DOUBLE_EQ(1, v.X());
  EXPECT_DOUBLE_EQ(2, v.Y());
  EXPECT_DOUBLE_EQ(3, v.Z());
}

/////////////////////////////////////////////////
TEST(UtilityTest, CovertMathVector2ToMsgs)
{
  msgs::Vector2d msg = msgs::Convert(math::Vector2d(1, 2));
  EXPECT_DOUBLE_EQ(1, msg.x());
  EXPECT_DOUBLE_EQ(2, msg.y());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMsgsVector2dToMath)
{
  msgs::Vector2d msg = msgs::Convert(math::Vector2d(1, 2));
  math::Vector2d v = msgs::Convert(msg);
  EXPECT_DOUBLE_EQ(1, v.X());
  EXPECT_DOUBLE_EQ(2, v.Y());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMathQuaterionToMsgs)
{
  msgs::Quaternion msg =
    msgs::Convert(math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI));

  EXPECT_TRUE(math::equal(msg.x(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(msg.y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(msg.z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(msg.w(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMsgsQuaterionToMath)
{
  msgs::Quaternion msg =
    msgs::Convert(math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI));
  math::Quaterniond v = msgs::Convert(msg);

  // TODO(anyone): to real unit test move math::equal to EXPECT_DOUBLE_EQ
  EXPECT_TRUE(math::equal(v.X(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(v.Y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(v.Z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(v.W(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertPoseMathToMsgs)
{
  msgs::Pose msg = msgs::Convert(math::Pose3d(
        math::Vector3d(1, 2, 3),
        math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI)));

  EXPECT_DOUBLE_EQ(1, msg.position().x());
  EXPECT_DOUBLE_EQ(2, msg.position().y());
  EXPECT_DOUBLE_EQ(3, msg.position().z());

  EXPECT_TRUE(math::equal(msg.orientation().x(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(msg.orientation().y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(msg.orientation().z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(msg.orientation().w(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMsgPoseToMath)
{
  msgs::Pose msg = msgs::Convert(
      math::Pose3d(math::Vector3d(1, 2, 3),
        math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI)));
  math::Pose3d v = msgs::Convert(msg);

  EXPECT_DOUBLE_EQ(1, v.Pos().X());
  EXPECT_DOUBLE_EQ(2, v.Pos().Y());
  EXPECT_DOUBLE_EQ(3, v.Pos().Z());
  EXPECT_TRUE(math::equal(v.Rot().X(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(v.Rot().Y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(v.Rot().Z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(v.Rot().W(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(MsgsTest, ConvertMathColorToMsgs)
{
  msgs::Color msg = msgs::Convert(math::Color(.1f, .2f, .3f, 1.0f));

  EXPECT_FLOAT_EQ(0.1f, msg.r());
  EXPECT_FLOAT_EQ(0.2f, msg.g());
  EXPECT_FLOAT_EQ(0.3f, msg.b());
  EXPECT_FLOAT_EQ(1.0f, msg.a());
}

/////////////////////////////////////////////////
TEST(MsgsTest, ConvertMsgsColorToMath)
{
  msgs::Color msg = msgs::Convert(math::Color(.1f, .2f, .3f, 1.0f));
  math::Color v = msgs::Convert(msg);

  EXPECT_FLOAT_EQ(0.1f, v.R());
  EXPECT_FLOAT_EQ(0.2f, v.G());
  EXPECT_FLOAT_EQ(0.3f, v.B());
  EXPECT_FLOAT_EQ(1.0f, v.A());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMathPlaneToMsgs)
{
  msgs::PlaneGeom msg = msgs::Convert(
      math::Planed(math::Vector3d(0, 0, 1),
        math::Vector2d(123, 456), 1.0));

  EXPECT_DOUBLE_EQ(0, msg.normal().x());
  EXPECT_DOUBLE_EQ(0, msg.normal().y());
  EXPECT_DOUBLE_EQ(1, msg.normal().z());

  EXPECT_DOUBLE_EQ(123, msg.size().x());
  EXPECT_DOUBLE_EQ(456, msg.size().y());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertMsgsPlaneToMath)
{
  msgs::PlaneGeom msg = msgs::Convert(
      math::Planed(math::Vector3d(0, 0, 1),
        math::Vector2d(123, 456), 1.0));
  math::Planed v = msgs::Convert(msg);

  EXPECT_DOUBLE_EQ(0, v.Normal().X());
  EXPECT_DOUBLE_EQ(0, v.Normal().Y());
  EXPECT_DOUBLE_EQ(1, v.Normal().Z());

  EXPECT_DOUBLE_EQ(123, v.Size().X());
  EXPECT_DOUBLE_EQ(456, v.Size().Y());

  EXPECT_TRUE(math::equal(1.0, v.Offset()));
}

/////////////////////////////////////////////////
TEST(MsgsTest, ConvertMathInertialToMsgs)
{
  const auto pose = ignition::math::Pose3d(5, 6, 7, 0.4, 0.5, 0.6);
  msgs::Inertial msg = msgs::Convert(
      ignition::math::Inertiald(
        ignition::math::MassMatrix3d(12.0,
          ignition::math::Vector3d(2, 3, 4),
          ignition::math::Vector3d(0.1, 0.2, 0.3)),
        pose));

  EXPECT_DOUBLE_EQ(12.0, msg.mass());
  EXPECT_DOUBLE_EQ(2.0, msg.ixx());
  EXPECT_DOUBLE_EQ(3.0, msg.iyy());
  EXPECT_DOUBLE_EQ(4.0, msg.izz());
  EXPECT_DOUBLE_EQ(0.1, msg.ixy());
  EXPECT_DOUBLE_EQ(0.2, msg.ixz());
  EXPECT_DOUBLE_EQ(0.3, msg.iyz());
  EXPECT_EQ(pose, msgs::Convert(msg.pose()));
}

/////////////////////////////////////////////////
TEST(MsgsTest, ConvertMsgsInertialToMath)
{
  const auto pose = ignition::math::Pose3d(5, 6, 7, 0.4, 0.5, 0.6);
  msgs::Inertial msg = msgs::Convert(
      ignition::math::Inertiald(
        ignition::math::MassMatrix3d(12.0,
          ignition::math::Vector3d(2, 3, 4),
          ignition::math::Vector3d(0.1, 0.2, 0.3)),
        pose));
  auto inertial = msgs::Convert(msg);

  EXPECT_DOUBLE_EQ(12.0, inertial.MassMatrix().Mass());
  EXPECT_DOUBLE_EQ(2.0, inertial.MassMatrix().Ixx());
  EXPECT_DOUBLE_EQ(3.0, inertial.MassMatrix().Iyy());
  EXPECT_DOUBLE_EQ(4.0, inertial.MassMatrix().Izz());
  EXPECT_DOUBLE_EQ(0.1, inertial.MassMatrix().Ixy());
  EXPECT_DOUBLE_EQ(0.2, inertial.MassMatrix().Ixz());
  EXPECT_DOUBLE_EQ(0.3, inertial.MassMatrix().Iyz());
  EXPECT_EQ(pose, inertial.Pose());
}

/////////////////////////////////////////////////
TEST(MsgsTest, ConvertMathMassMatrix3ToMsgs)
{
  msgs::Inertial msg = msgs::Convert(
      ignition::math::MassMatrix3d(12.0,
        ignition::math::Vector3d(2, 3, 4),
        ignition::math::Vector3d(0.1, 0.2, 0.3)));

  EXPECT_DOUBLE_EQ(12.0, msg.mass());
  EXPECT_DOUBLE_EQ(2.0, msg.ixx());
  EXPECT_DOUBLE_EQ(3.0, msg.iyy());
  EXPECT_DOUBLE_EQ(4.0, msg.izz());
  EXPECT_DOUBLE_EQ(0.1, msg.ixy());
  EXPECT_DOUBLE_EQ(0.2, msg.ixz());
  EXPECT_DOUBLE_EQ(0.3, msg.iyz());
  EXPECT_EQ(ignition::math::Pose3d::Zero, msgs::Convert(msg.pose()));
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertStringMsg)
{
  msgs::StringMsg msg = msgs::Convert(std::string("a string msg"));
  EXPECT_EQ("a string msg", msg.data());

  std::string s = msgs::Convert(msg);
  EXPECT_EQ(s, "a string msg");
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertBoolean)
{
  msgs::Boolean msg = msgs::Convert(static_cast<bool>(true));
  EXPECT_EQ(true, msg.data());

  bool s = msgs::Convert(msg);
  EXPECT_EQ(s, true);
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertInt32)
{
  msgs::Int32 msg = msgs::Convert(static_cast<int32_t>(-543));
  EXPECT_EQ(-543, msg.data());

  int s = msgs::Convert(msg);
  EXPECT_EQ(s, -543);
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertUInt32)
{
  msgs::UInt32 msg = msgs::Convert(123456u);
  EXPECT_EQ(123456u, msg.data());

  uint32_t s = msgs::Convert(msg);
  EXPECT_EQ(s, 123456u);
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertInt64)
{
  msgs::Int64 msg = msgs::Convert(std::numeric_limits<int64_t>::min());
  EXPECT_EQ(std::numeric_limits<int64_t>::min(), msg.data());

  int64_t s = msgs::Convert(msg);
  EXPECT_EQ(s, std::numeric_limits<int64_t>::min());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertUInt64)
{
  msgs::UInt64 msg = msgs::Convert(std::numeric_limits<uint64_t>::max());
  EXPECT_EQ(std::numeric_limits<uint64_t>::max(), msg.data());

  uint64_t s = msgs::Convert(msg);
  EXPECT_EQ(s, std::numeric_limits<uint64_t>::max());
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertDouble)
{
  msgs::Double msg = msgs::Convert(static_cast<double>(-33.888));
  EXPECT_DOUBLE_EQ(-33.888, msg.data());

  double s = msgs::Convert(msg);
  EXPECT_DOUBLE_EQ(s, -33.888);
}

/////////////////////////////////////////////////
TEST(UtilityTest, ConvertFloat)
{
  msgs::Float msg = msgs::Convert(0.999f);
  EXPECT_DOUBLE_EQ(0.999f, msg.data());

  float s = msgs::Convert(msg);
  EXPECT_DOUBLE_EQ(s, 0.999f);
}

/////////////////////////////////////////////////
TEST(UtilityTest, SetVector3)
{
  msgs::Vector3d msg;
  msgs::Set(&msg, math::Vector3d(1, 2, 3));
  EXPECT_DOUBLE_EQ(1, msg.x());
  EXPECT_DOUBLE_EQ(2, msg.y());
  EXPECT_DOUBLE_EQ(3, msg.z());
}

/////////////////////////////////////////////////
TEST(UtilityTest, SetVector2d)
{
  msgs::Vector2d msg;
  msgs::Set(&msg, math::Vector2d(1, 2));
  EXPECT_DOUBLE_EQ(1, msg.x());
  EXPECT_DOUBLE_EQ(2, msg.y());
}

/////////////////////////////////////////////////
TEST(UtilityTest, SetQuaternion)
{
  msgs::Quaternion msg;
  msgs::Set(&msg, math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI));
  EXPECT_TRUE(math::equal(msg.x(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(msg.y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(msg.z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(msg.w(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(UtilityTest, SetPose)
{
  msgs::Pose msg;
  msgs::Set(&msg, math::Pose3d(math::Vector3d(1, 2, 3),
        math::Quaterniond(IGN_PI * 0.25, IGN_PI * 0.5, IGN_PI)));

  EXPECT_DOUBLE_EQ(1, msg.position().x());
  EXPECT_DOUBLE_EQ(2, msg.position().y());
  EXPECT_DOUBLE_EQ(3, msg.position().z());

  EXPECT_TRUE(math::equal(msg.orientation().x(), -0.65328148243818818));
  EXPECT_TRUE(math::equal(msg.orientation().y(), 0.27059805007309856));
  EXPECT_TRUE(math::equal(msg.orientation().z(), 0.65328148243818829));
  EXPECT_TRUE(math::equal(msg.orientation().w(), 0.27059805007309851));
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetColor)
{
  msgs::Color msg;
  msgs::Set(&msg, math::Color(.1f, .2f, .3f, 1.0f));
  EXPECT_FLOAT_EQ(0.1f, msg.r());
  EXPECT_FLOAT_EQ(0.2f, msg.g());
  EXPECT_FLOAT_EQ(0.3f, msg.b());
  EXPECT_FLOAT_EQ(1.0f, msg.a());
}

/////////////////////////////////////////////////
TEST(UtilityTest, SetPlane)
{
  msgs::PlaneGeom msg;
  msgs::Set(&msg, math::Planed(
        math::Vector3d(0, 0, 1),
        math::Vector2d(123, 456), 1.0));

  EXPECT_DOUBLE_EQ(0, msg.normal().x());
  EXPECT_DOUBLE_EQ(0, msg.normal().y());
  EXPECT_DOUBLE_EQ(1, msg.normal().z());

  EXPECT_DOUBLE_EQ(123, msg.size().x());
  EXPECT_DOUBLE_EQ(456, msg.size().y());

  EXPECT_TRUE(math::equal(1.0, msg.d()));
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetInertial)
{
  const auto pose = ignition::math::Pose3d(5, 6, 7, 0.4, 0.5, 0.6);
  msgs::Inertial msg;
  msgs::Set(&msg, ignition::math::Inertiald(
      ignition::math::MassMatrix3d(
        12.0,
        ignition::math::Vector3d(2, 3, 4),
        ignition::math::Vector3d(0.1, 0.2, 0.3)),
      pose));

  EXPECT_DOUBLE_EQ(12.0, msg.mass());
  EXPECT_DOUBLE_EQ(2.0, msg.ixx());
  EXPECT_DOUBLE_EQ(3.0, msg.iyy());
  EXPECT_DOUBLE_EQ(4.0, msg.izz());
  EXPECT_DOUBLE_EQ(0.1, msg.ixy());
  EXPECT_DOUBLE_EQ(0.2, msg.ixz());
  EXPECT_DOUBLE_EQ(0.3, msg.iyz());
  EXPECT_EQ(pose, msgs::Convert(msg.pose()));
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetMassMatrix3)
{
  msgs::Inertial msg;
  msgs::Set(&msg, ignition::math::MassMatrix3d(
        12.0,
        ignition::math::Vector3d(2, 3, 4),
        ignition::math::Vector3d(0.1, 0.2, 0.3)));

  EXPECT_DOUBLE_EQ(12.0, msg.mass());
  EXPECT_DOUBLE_EQ(2.0, msg.ixx());
  EXPECT_DOUBLE_EQ(3.0, msg.iyy());
  EXPECT_DOUBLE_EQ(4.0, msg.izz());
  EXPECT_DOUBLE_EQ(0.1, msg.ixy());
  EXPECT_DOUBLE_EQ(0.2, msg.ixz());
  EXPECT_DOUBLE_EQ(0.3, msg.iyz());
  EXPECT_EQ(ignition::math::Pose3d::Zero, msgs::Convert(msg.pose()));
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetStringMsg)
{
  msgs::StringMsg msg;
  msgs::Set(&msg, "a string msg");

  EXPECT_EQ("a string msg", msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetBoolean)
{
  msgs::Boolean msg;
  msgs::Set(&msg, false);

  EXPECT_FALSE(msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetInt32)
{
  msgs::Int32 msg;
  msgs::Set(&msg, 9976);

  EXPECT_EQ(9976, msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetUInt32)
{
  msgs::UInt32 msg;
  msgs::Set(&msg, 0u);

  EXPECT_EQ(0u, msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetInt64)
{
  msgs::Int64 msg;
  msgs::Set(&msg, std::numeric_limits<int64_t>::max());

  EXPECT_EQ(std::numeric_limits<int64_t>::max(), msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetUInt64)
{
  msgs::UInt64 msg;
  msgs::Set(&msg, std::numeric_limits<uint64_t>::min());

  EXPECT_EQ(std::numeric_limits<uint64_t>::min(), msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetDouble)
{
  msgs::Double msg;
  msgs::Set(&msg, 0.123);

  EXPECT_DOUBLE_EQ(0.123, msg.data());
}

/////////////////////////////////////////////////
TEST(MsgsTest, SetFloat)
{
  msgs::Float msg;
  msgs::Set(&msg, -367.0f);

  EXPECT_DOUBLE_EQ(-367.0f, msg.data());
}

/////////////////////////////////////////////////
TEST(UtilityTest, Initialization)
{
  {
    msgs::Vector3d msg;
    EXPECT_DOUBLE_EQ(0, msg.x());
    EXPECT_DOUBLE_EQ(0, msg.y());
    EXPECT_DOUBLE_EQ(0, msg.z());
  }

  {
    msgs::Wrench msg;
    EXPECT_DOUBLE_EQ(0, msg.force().x());
    EXPECT_DOUBLE_EQ(0, msg.force().y());
    EXPECT_DOUBLE_EQ(0, msg.force().z());
    EXPECT_DOUBLE_EQ(0, msg.torque().x());
    EXPECT_DOUBLE_EQ(0, msg.torque().y());
    EXPECT_DOUBLE_EQ(0, msg.torque().z());
  }
}

//////////////////////////////////////////////////
void CompareMsgsJointTypeToString(const msgs::Joint::Type _type)
{
  EXPECT_EQ(_type, msgs::ConvertJointType(msgs::ConvertJointType(_type)));
}

//////////////////////////////////////////////////
TEST(MsgsTest, ConvertMsgsJointTypeToString)
{
  CompareMsgsJointTypeToString(msgs::Joint::REVOLUTE);
  CompareMsgsJointTypeToString(msgs::Joint::REVOLUTE2);
  CompareMsgsJointTypeToString(msgs::Joint::PRISMATIC);
  CompareMsgsJointTypeToString(msgs::Joint::UNIVERSAL);
  CompareMsgsJointTypeToString(msgs::Joint::BALL);
  CompareMsgsJointTypeToString(msgs::Joint::SCREW);
  CompareMsgsJointTypeToString(msgs::Joint::GEARBOX);
  CompareMsgsJointTypeToString(msgs::Joint::FIXED);

  EXPECT_EQ(msgs::ConvertJointType("bad type"), msgs::Joint::REVOLUTE);
  EXPECT_EQ(msgs::ConvertJointType(msgs::Joint::Type(100)), "unknown");
}

//////////////////////////////////////////////////
void CompareMsgsGeometryTypeToString(const msgs::Geometry::Type _type)
{
  EXPECT_EQ(_type, msgs::ConvertGeometryType(msgs::ConvertGeometryType(_type)));
}

//////////////////////////////////////////////////
TEST(MsgsTest, ConvertMsgsGeometryTypeToString)
{
  CompareMsgsGeometryTypeToString(msgs::Geometry::BOX);
  CompareMsgsGeometryTypeToString(msgs::Geometry::SPHERE);
  CompareMsgsGeometryTypeToString(msgs::Geometry::CYLINDER);
  CompareMsgsGeometryTypeToString(msgs::Geometry::PLANE);
  CompareMsgsGeometryTypeToString(msgs::Geometry::IMAGE);
  CompareMsgsGeometryTypeToString(msgs::Geometry::HEIGHTMAP);
  CompareMsgsGeometryTypeToString(msgs::Geometry::MESH);
  CompareMsgsGeometryTypeToString(msgs::Geometry::POLYLINE);

  EXPECT_EQ(msgs::ConvertGeometryType("bad type"), msgs::Geometry::BOX);
  EXPECT_EQ(msgs::ConvertGeometryType(msgs::Geometry::Type(100)), "unknown");
}

//////////////////////////////////////////////////
void CompareMsgsShaderTypeToString(const msgs::Material::ShaderType _type)
{
  EXPECT_EQ(_type, msgs::ConvertShaderType(msgs::ConvertShaderType(_type)));
}

//////////////////////////////////////////////////
TEST(MsgsTest, ConvertMsgsShaderTypeToString)
{
  CompareMsgsShaderTypeToString(msgs::Material::NORMAL_MAP_OBJECT_SPACE);
  CompareMsgsShaderTypeToString(msgs::Material::NORMAL_MAP_TANGENT_SPACE);
  CompareMsgsShaderTypeToString(msgs::Material::PIXEL);
  CompareMsgsShaderTypeToString(msgs::Material::VERTEX);

  EXPECT_EQ(msgs::ConvertShaderType("bad type"), msgs::Material::VERTEX);
  EXPECT_EQ(msgs::ConvertShaderType(msgs::Material::ShaderType(100)),
      "unknown");
}

/////////////////////////////////////////////////
TEST(UtilityTest, CovertMathAxisAlignedBox)
{
  // Convert from math to msg
  msgs::AxisAlignedBox msg = msgs::Convert(
      math::AxisAlignedBox(-1, -2, -3, 12, 15, 20));
  EXPECT_DOUBLE_EQ(-1, msg.min_corner().x());
  EXPECT_DOUBLE_EQ(-2, msg.min_corner().y());
  EXPECT_DOUBLE_EQ(-3, msg.min_corner().z());

  EXPECT_DOUBLE_EQ(12, msg.max_corner().x());
  EXPECT_DOUBLE_EQ(15, msg.max_corner().y());
  EXPECT_DOUBLE_EQ(20, msg.max_corner().z());

  // Convert from msg to math
  math::AxisAlignedBox aab = msgs::Convert(msg);
  EXPECT_DOUBLE_EQ(-1, aab.Min().X());
  EXPECT_DOUBLE_EQ(-2, aab.Min().Y());
  EXPECT_DOUBLE_EQ(-3, aab.Min().Z());

  EXPECT_DOUBLE_EQ(12, aab.Max().X());
  EXPECT_DOUBLE_EQ(15, aab.Max().Y());
  EXPECT_DOUBLE_EQ(20, aab.Max().Z());

  // Set msg from math
  aab = msgs::Convert(msg);
  msgs::AxisAlignedBox msg2;
  msgs::Set(&msg2, aab);
  EXPECT_DOUBLE_EQ(-1, msg2.min_corner().x());
  EXPECT_DOUBLE_EQ(-2, msg2.min_corner().y());
  EXPECT_DOUBLE_EQ(-3, msg2.min_corner().z());

  EXPECT_DOUBLE_EQ(12, msg2.max_corner().x());
  EXPECT_DOUBLE_EQ(15, msg2.max_corner().y());
  EXPECT_DOUBLE_EQ(20, msg2.max_corner().z());

  // Try different values with Set
  aab.Min() = math::Vector3d(-23.4, 56.2, -123.5);
  aab.Max() = math::Vector3d(34.1, 92.1, -723.2);
  msgs::Set(&msg2, aab);
  EXPECT_DOUBLE_EQ(-23.4, msg2.min_corner().x());
  EXPECT_DOUBLE_EQ(56.2, msg2.min_corner().y());
  EXPECT_DOUBLE_EQ(-123.5, msg2.min_corner().z());

  EXPECT_DOUBLE_EQ(34.1, msg2.max_corner().x());
  EXPECT_DOUBLE_EQ(92.1, msg2.max_corner().y());
  EXPECT_DOUBLE_EQ(-723.2, msg2.max_corner().z());
}

/////////////////////////////////////////////////
TEST(UtilityTest, InitPointCloudPacked)
{
  msgs::PointCloudPacked pc;

  msgs::InitPointCloudPacked(pc, "my_frame", true,
      {{"xyz", msgs::PointCloudPacked::Field::FLOAT32},
      {"rgb", msgs::PointCloudPacked::Field::FLOAT32}});

  EXPECT_EQ(4, pc.field_size());
  EXPECT_EQ(24u, pc.point_step());

  EXPECT_EQ("x", pc.field(0).name());
  EXPECT_EQ(0u, pc.field(0).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(0).datatype());
  EXPECT_EQ(1u, pc.field(0).count());

  EXPECT_EQ("y", pc.field(1).name());
  EXPECT_EQ(4u, pc.field(1).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(1).datatype());
  EXPECT_EQ(1u, pc.field(1).count());

  EXPECT_EQ("z", pc.field(2).name());
  EXPECT_EQ(8u, pc.field(2).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(2).datatype());
  EXPECT_EQ(1u, pc.field(2).count());

  EXPECT_EQ("rgb", pc.field(3).name());
  EXPECT_EQ(16u, pc.field(3).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(3).datatype());
  EXPECT_EQ(1u, pc.field(3).count());

  // Don't align to word boundaries
  msgs::InitPointCloudPacked(pc, "my_frame", false,
      {{"xyz", msgs::PointCloudPacked::Field::FLOAT32},
      {"rgb", msgs::PointCloudPacked::Field::FLOAT32}});
  EXPECT_EQ(4, pc.field_size());
  EXPECT_EQ(16u, pc.point_step());

  EXPECT_EQ("x", pc.field(0).name());
  EXPECT_EQ(0u, pc.field(0).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(0).datatype());
  EXPECT_EQ(1u, pc.field(0).count());

  EXPECT_EQ("y", pc.field(1).name());
  EXPECT_EQ(4u, pc.field(1).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(1).datatype());
  EXPECT_EQ(1u, pc.field(1).count());

  EXPECT_EQ("z", pc.field(2).name());
  EXPECT_EQ(8u, pc.field(2).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(2).datatype());
  EXPECT_EQ(1u, pc.field(2).count());

  EXPECT_EQ("rgb", pc.field(3).name());
  EXPECT_EQ(12u, pc.field(3).offset());
  EXPECT_EQ(msgs::PointCloudPacked::Field::FLOAT32, pc.field(3).datatype());
  EXPECT_EQ(1u, pc.field(3).count());
  EXPECT_EQ("my_frame", pc.header().data(0).value(0));
  EXPECT_EQ("frame_id", pc.header().data(0).key());

  // Test data types
  msgs::InitPointCloudPacked(pc, "my_new_frame", false,
      {{"x", msgs::PointCloudPacked::Field::INT8},
       {"y", msgs::PointCloudPacked::Field::UINT8},
       {"z", msgs::PointCloudPacked::Field::INT16},
       {"r", msgs::PointCloudPacked::Field::UINT16},
       {"s", msgs::PointCloudPacked::Field::INT32},
       {"t", msgs::PointCloudPacked::Field::UINT32},
       {"u", msgs::PointCloudPacked::Field::FLOAT64}});

  EXPECT_EQ("frame_id", pc.header().data(0).key());
  EXPECT_EQ("my_new_frame", pc.header().data(0).value(0));

  EXPECT_EQ(0u, pc.field(0).offset());
  EXPECT_EQ(1u, pc.field(1).offset());
  EXPECT_EQ(2u, pc.field(2).offset());
  EXPECT_EQ(4u, pc.field(3).offset());
  EXPECT_EQ(6u, pc.field(4).offset());
  EXPECT_EQ(10u, pc.field(5).offset());
  EXPECT_EQ(14u, pc.field(6).offset());
  EXPECT_EQ(22u, pc.point_step());
}
