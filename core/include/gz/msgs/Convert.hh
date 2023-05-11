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
#ifndef GZ_MSGS_CONVERT_HH_
#define GZ_MSGS_CONVERT_HH_

#include <string>
#include <utility>
#include <vector>

#include "gz/msgs/config.hh"
#include "gz/msgs/Export.hh"

#if not __has_include(<gz/msgs/MessageTypes.hh>)
 static_assert(false, "something is wrong")
#endif

/// \file Utility.hh
/// \brief Utility functions that support conversion between message type
/// and Gazebo Math types.

namespace gz::msgs
{
  // Inline bracket to help doxygen filtering.
  inline namespace GZ_MSGS_VERSION_NAMESPACE {

  template <typename GzMsgT, typename T>
  struct Converter {
    static void Convert(const GzMsgT& in, T& out);
    static void Convert(const T& in, GzMsgT& out);
  };

  template <typename GzMsgT, typename T>
  T Convert(const GzMsgT &_msg) {
    T ret;
    Converter<GzMsgT, T>::Convert(_msg, ret);
    return ret;
  }
  }
}  // namespace gz::msgs

#endif
