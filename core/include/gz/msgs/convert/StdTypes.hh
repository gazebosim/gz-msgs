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
#ifndef GZ_MSGS_CONVERT_STDTYPES_HH_
#define GZ_MSGS_CONVERT_STDTYPES_HH_

#include <gz/math/Helpers.hh>

#include <gz/msgs/Converter.hh>

// Message Headers
#include "gz/msgs/boolean.pb.h"
#include "gz/msgs/double.pb.h"
#include "gz/msgs/float.pb.h"
#include "gz/msgs/int32.pb.h"
#include "gz/msgs/int64.pb.h"
#include "gz/msgs/stringmsg.pb.h"
#include "gz/msgs/time.pb.h"
#include "gz/msgs/uint32.pb.h"
#include "gz/msgs/uint64.pb.h"

// Data Headers
#include <chrono>
#include <string>
#include <utility>

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

/////////////////////////////////
template<>
inline void
Converter<gz::msgs::Time, std::chrono::steady_clock::duration>::Set(
    gz::msgs::Time *_msg, const std::chrono::steady_clock::duration &_data)
{
  std::pair<uint64_t, uint64_t> timeSecAndNsecs =
        gz::math::durationToSecNsec(_data);
  msgs::Time msg;
  _msg->set_sec(timeSecAndNsecs.first);
  _msg->set_nsec(timeSecAndNsecs.second);
}

template<>
inline void
Converter<gz::msgs::Time, std::chrono::steady_clock::duration>::Set(
    std::chrono::steady_clock::duration *_data, const gz::msgs::Time &_msg)
{
  *_data = (
      std::chrono::seconds(_msg.sec()) +
      std::chrono::nanoseconds(_msg.nsec()));
}

inline gz::msgs::Time
Convert(const std::chrono::steady_clock::duration &_data)
{
  return Converter<gz::msgs::Time,
                   std::chrono::steady_clock::duration>::Convert(_data);
}

inline std::chrono::steady_clock::duration
Convert(const gz::msgs::Time &_msg)
{
  return Converter<gz::msgs::Time,
                   std::chrono::steady_clock::duration>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void
Converter<gz::msgs::StringMsg, std::string>::Set(
    gz::msgs::StringMsg *_msg, const std::string &_data)
{
  _msg->set_data(_data);
}

template<>
inline void
Converter<gz::msgs::StringMsg, std::string>::Set(
    std::string *_data, const gz::msgs::StringMsg &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::StringMsg
Convert(const std::string &_data)
{
  return Converter<gz::msgs::StringMsg, std::string>::Convert(_data);
}

inline std::string Convert(const gz::msgs::StringMsg &_msg)
{
  return Converter<gz::msgs::StringMsg, std::string>::Convert(_msg);
}

inline void Set(gz::msgs::StringMsg *_msg, const char *_data)
{
  _msg->set_data(_data);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Boolean, bool>::Set(
    gz::msgs::Boolean *_msg, const bool &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::Boolean, bool>::Set(
    bool *_data, const gz::msgs::Boolean &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::Boolean Convert(const bool &_data)
{
  return Converter<gz::msgs::Boolean, bool>::Convert(_data);
}

inline bool Convert(const gz::msgs::Boolean &_msg)
{
  return Converter<gz::msgs::Boolean, bool>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Int32, int32_t>::Set(
    gz::msgs::Int32 *_msg, const int32_t &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::Int32, int32_t>::Set(
    int32_t *_data, const gz::msgs::Int32 &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::Int32 Convert(const int32_t &_data)
{
  return Converter<gz::msgs::Int32, int32_t>::Convert(_data);
}

inline int32_t Convert(const gz::msgs::Int32 &_msg)
{
  return Converter<gz::msgs::Int32, int32_t>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::UInt32, uint32_t>::Set(
    gz::msgs::UInt32 *_msg, const uint32_t &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::UInt32, uint32_t>::Set(
    uint32_t *_data, const gz::msgs::UInt32 &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::UInt32 Convert(const uint32_t &_data)
{
  return Converter<gz::msgs::UInt32, uint32_t>::Convert(_data);
}

inline uint32_t Convert(const gz::msgs::UInt32 &_msg)
{
  return Converter<gz::msgs::UInt32, uint32_t>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Int64, int64_t>::Set(
    gz::msgs::Int64 *_msg, const int64_t &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::Int64, int64_t>::Set(
    int64_t *_data, const gz::msgs::Int64 &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::Int64 Convert(const int64_t &_data)
{
  return Converter<gz::msgs::Int64, int64_t>::Convert(_data);
}

inline int64_t Convert(const gz::msgs::Int64 &_msg)
{
  return Converter<gz::msgs::Int64, int64_t>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::UInt64, uint64_t>::Set(
    gz::msgs::UInt64 *_msg, const uint64_t &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::UInt64, uint64_t>::Set(
    uint64_t *_data, const gz::msgs::UInt64 &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::UInt64 Convert(const uint64_t &_data)
{
  return Converter<gz::msgs::UInt64, uint64_t>::Convert(_data);
}

inline uint64_t Convert(const gz::msgs::UInt64 &_msg)
{
  return Converter<gz::msgs::UInt64, uint64_t>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Float, float>::Set(
    gz::msgs::Float *_msg, const float &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::Float, float>::Set(
    float *_data, const gz::msgs::Float &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::Float Convert(const float &_data)
{
  return Converter<gz::msgs::Float, float>::Convert(_data);
}

inline float Convert(const gz::msgs::Float &_msg)
{
  return Converter<gz::msgs::Float, float>::Convert(_msg);
}

/////////////////////////////////
template<>
inline void Converter<gz::msgs::Double, double>::Set(
    gz::msgs::Double *_msg, const double &_data)
{
  _msg->set_data(_data);
}

template<>
inline void Converter<gz::msgs::Double, double>::Set(
    double *_data, const gz::msgs::Double &_msg)
{
  *_data = _msg.data();
}

inline gz::msgs::Double Convert(const double &_data)
{
  return Converter<gz::msgs::Double, double>::Convert(_data);
}

inline double Convert(const gz::msgs::Double &_msg)
{
  return Converter<gz::msgs::Double, double>::Convert(_msg);
}
}  // namespce
}  // namespace gz::msgs
#endif  // GZ_MSGS_CONVERT_VECTOR3_HH_
