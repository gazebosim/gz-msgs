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
#ifndef GZ_MSGS_CONVERTER_HH_
#define GZ_MSGS_CONVERTER_HH_

#include <type_traits>
#include <google/protobuf/message.h>

#include "gz/msgs/Export.hh"

namespace gz::msgs {
// Inline bracket to help doxygen filtering.
inline namespace GZ_MSGS_VERSION_NAMESPACE {

template <typename MessageT,
  typename DataT,
  std::enable_if_t<
    std::is_base_of_v<
      google::protobuf::Message, MessageT>, bool> = true>
struct GZ_MSGS_VISIBLE Converter
{
  static void Set(MessageT *_msg, const DataT &_data);
  static void Set(DataT *_data, const MessageT &_msg);

  static DataT Convert(const MessageT &_msg){
    DataT ret;
    Converter<MessageT, DataT>::Set(&ret, _msg);
    return ret;
  }

  static MessageT Convert(const DataT &_data){
    MessageT ret;
    Converter<MessageT, DataT>::Set(&ret, _data);
    return ret;
  }
};

template <typename MessageT,
  typename DataT,
  std::enable_if_t<
    std::is_base_of_v<
      google::protobuf::Message, MessageT>, bool> = true>
GZ_MSGS_VISIBLE void Set(MessageT *_msg, const DataT &_data)
{
  Converter<MessageT, DataT>::Set(_msg, _data);
}

template <typename MessageT,
  typename DataT,
  std::enable_if_t<
    std::is_base_of_v<
      google::protobuf::Message, MessageT>, bool> = true>
GZ_MSGS_VISIBLE void Set(DataT *_data , const MessageT &_msg)
{
  Converter<MessageT, DataT>::Set(_data, _msg);
}
}  // namespace
}  // namespace gz::msgs
#endif  // GZ_MSGS_CONVERTER_HH_
