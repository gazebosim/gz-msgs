/*
 * Copyright (C) 2022 Open Source Robotics Foundation
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

// Inspired by
// https://github.com/ros/common_msgs/blob/275b09a/sensor_msgs/include/sensor_msgs/point_cloud2_iterator.h

#ifndef IGNITION_MSGS_POINTCLOUDPACKEDUTILS_HH_
#define IGNITION_MSGS_POINTCLOUDPACKEDUTILS_HH_

#include <ignition/msgs/pointcloud_packed.pb.h>

#include <cstdarg>
#include <sstream>
#include <string>
#include <vector>

#include "ignition/msgs/config.hh"
#include "ignition/msgs/detail/PointCloudPackedUtils.hh"

namespace ignition
{
namespace msgs
{
/// \brief Class that can iterate over a PointCloudPacked message.
///
/// E.g, you create your message and reserve space for data as follows:
///
/// \code{.cpp}
/// ignition::msgs::PointCloudPacked pcMsg;
/// ignition::msgs::InitPointCloudPacked(pcMsg, "my_new_frame", false,
///     {{"a", PointCloudPacked::Field::FLOAT32}});
/// pcMsg.mutable_data()->resize(numPts * pcMsg.point_step());
/// \endcode
///
/// For iterating over "a", you do :
///
/// \code{.cpp}
/// ignition::msgs::PointCloudPackedIterator<float> iterA(pcMsg, "a");
/// \endcode
///
/// And then access it through iterA[0] or *iterA.
///
/// For iterating over RGBA, you can access each element as uint8_t:
///
/// \code{.cpp}
/// ignition::msgs::PointCloudPackedIterator<uint8_t> iterR(pcMsg, "r");
/// ignition::msgs::PointCloudPackedIterator<uint8_t> iterG(pcMsg, "g");
/// ignition::msgs::PointCloudPackedIterator<uint8_t> iterB(pcMsg, "b");
/// ignition::msgs::PointCloudPackedIterator<uint8_t> iterA(pcMsg, "a");
/// \endcode
///
/// \tparam FieldType Type of the element being iterated upon
template<typename FieldType>
class PointCloudPackedIterator
  : public PointCloudPackedIteratorBase<
    FieldType, FieldType, char, PointCloudPacked, PointCloudPackedIterator>
{
  // Documentation inherited
  public: PointCloudPackedIterator(PointCloudPacked &_cloudMsg,
    const std::string &_fieldName)
      : PointCloudPackedIteratorBase<FieldType, FieldType, char,
        PointCloudPacked, PointCloudPackedIterator>
        ::PointCloudPackedIteratorBase(_cloudMsg, _fieldName)
  {
  }
};

/// \brief Same as a PointCloudPackedIterator but for const data
/// \tparam FieldType Type of the element being iterated upon
template<typename FieldType>
class PointCloudPackedConstIterator
  : public PointCloudPackedIteratorBase<
    FieldType, const FieldType, const char, const PointCloudPacked,
    PointCloudPackedConstIterator>
{
  public: PointCloudPackedConstIterator(
      const PointCloudPacked &_cloudMsg,
      const std::string &_fieldName)
    : PointCloudPackedIteratorBase<FieldType, const FieldType, const char,
        const PointCloudPacked,
        PointCloudPackedConstIterator
    >::PointCloudPackedIteratorBase(_cloudMsg, _fieldName)
    {
    }
};

/// \brief Return the size of a datatype (which is an enum of
/// ignition::msgs::PointCloudPacked::Field) in bytes.
/// \param[in] _dataType One of the enums of
///            ignition::msgs::PointCloudPacked::Field
/// \return Size in bytes. Returns -1 if the type is unknown.
inline int sizeOfPointField(
    PointCloudPacked::Field::DataType _dataType)
{
  if ((_dataType == PointCloudPacked::Field::INT8) ||
      (_dataType == PointCloudPacked::Field::UINT8))
  {
    return 1;
  }
  else if ((_dataType == PointCloudPacked::Field::INT16) ||
           (_dataType == PointCloudPacked::Field::UINT16))
  {
    return 2;
  }
  else if ((_dataType == PointCloudPacked::Field::INT32) ||
           (_dataType == PointCloudPacked::Field::UINT32) ||
           (_dataType == PointCloudPacked::Field::FLOAT32))
  {
    return 4;
  }
  else if (_dataType == PointCloudPacked::Field::FLOAT64)
  {
    return 8;
  }
  else
  {
    std::cerr << "PointCloudPacked::Field of type [" << _dataType
              << "] does not exist" << std::endl;
  }
  return -1;
}
}
}

#endif
