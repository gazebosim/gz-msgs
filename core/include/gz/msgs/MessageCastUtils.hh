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

#ifndef GZ_MSGS_MESSAGE_CAST_UTILS_HH_
#define GZ_MSGS_MESSAGE_CAST_UTILS_HH_

#include <memory>

#include <google/protobuf/message.h>
#include <google/protobuf/message_lite.h>

namespace gz::msgs
{

// A helper to do a dynamic cast from a generic proto message to a concrete
// type. In newer versions of protobuf, the helper `DynamicCastMessage` is
// available and should be used.
template <typename T>
const T* DoDynamicCastMessage(const google::protobuf::MessageLite* message)
{
#if GOOGLE_PROTOBUF_VERSION >= 5028000
  return google::protobuf::DynamicCastMessage<T>(message);
#else
  return dynamic_cast<const T*>(message);
#endif
}

// A helper to do a dynamic cast from a generic proto message to a concrete
// type. In newer versions of protobuf, the helper `DynamicCastMessage` is
// available and should be used.
template <typename T>
T* DoDynamicCastMessage(google::protobuf::MessageLite* message)
{
#if GOOGLE_PROTOBUF_VERSION >= 5028000
  return google::protobuf::DynamicCastMessage<T>(message);
#else
  return dynamic_cast<T*>(message);
#endif
}

// A helper to do a dynamic pointer cast from a shared_ptr to a generic proto
// message to a concrete type. In newer versions of protobuf, the helper
// `DynamicCastMessage` is available and should be used.
template <typename T>
std::shared_ptr<T> DoDynamicCastMessage(
    std::shared_ptr<google::protobuf::MessageLite> message)
{
#if GOOGLE_PROTOBUF_VERSION >= 6030000
  return google::protobuf::DynamicCastMessage<T>(std::move(message));
#else
  return std::dynamic_pointer_cast<T>(std::move(message));
#endif
}

// A helper to do a dynamic cast from a unique_ptr to a generic proto message
// to a concrete type. In newer versions of protobuf, the helper
// `DynamicCastMessage` is available and should be used.
template <typename MsgT>
std::unique_ptr<MsgT> DoDynamicCastMessage(
    std::unique_ptr<google::protobuf::Message>&& _baseMsg)
{
#if GOOGLE_PROTOBUF_VERSION >= 5028000
  auto converted = std::unique_ptr<MsgT>{
      google::protobuf::DynamicCastMessage<MsgT>(_baseMsg.get())};
#else
  auto converted = std::unique_ptr<MsgT>{dynamic_cast<MsgT*>(_baseMsg.get())};
#endif
  if (converted) {
    // transfer ownership to a new unique_ptr object by releasing from old one
    (void) _baseMsg.release();
  }
  return converted;
}

}  // namespace gz::msgs

#endif  // GZ_MSGS_MESSAGE_CAST_UTILS_HH_
