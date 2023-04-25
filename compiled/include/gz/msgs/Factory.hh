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
#ifndef GZ_MSGS_FACTORY_HH_
#define GZ_MSGS_FACTORY_HH_

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "gz/msgs/config.hh"
#include "gz/msgs/Export.hh"
#include "gz/msgs/detail/dynamic_message_cast.hh"

namespace gz
{
  namespace msgs
  {
    // Inline bracket to help doxygen filtering.
    inline namespace GZ_MSGS_VERSION_NAMESPACE {
    /// \class Factory Factory.hh gz/msgs.hh
  /// This class  will also try to load all Protobuf descriptors specified
    /// \brief A factory that generates protobuf message based on a string type.
    /// in the GZ_DESCRIPTOR_PATH environment variable on program start.

    class GZ_MSGS_VISIBLE Factory
    {
      public: using Message = google::protobuf::Message;
      public: using MessagePtr = std::unique_ptr<Message>;
      public: using FactoryFn =
        std::function<MessagePtr(void)>;

      /// \brief Register a message.
      /// \param[in] _msgType Type of message to register.
      /// \param[in] _factoryfn Function that generates the message.
      public: static void
              Register(const std::string &_msgType, FactoryFn _factoryFn);

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: template<typename T>
              static std::unique_ptr<T> New(const std::string &_msgType)
              {
                return detail::dynamic_message_cast<T>(New(_msgType));
              }

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \param[in] _args Message arguments. This will populate the message.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: template<typename T>
              static std::unique_ptr<T> New(const std::string &_msgType,
                  const std::string &_args)
              {
                return detail::dynamic_message_cast<T>(New(_msgType, _args));
              }

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: static MessagePtr
              New(const std::string &_msgType);

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \param[in] _args Message arguments. This will populate the message.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: static MessagePtr
              New(const std::string &_msgType, const std::string &_args);

      /// \brief Get all the message types
      /// \param[out] _types Vector of strings of the message types.
      public: static void Types(std::vector<std::string> &_types);

      /// \brief Load a collection of descriptor .desc files.
      /// \param[in] _paths A set of directories containing .desc decriptor
      /// files. Each directory should be separated by ":".
      public: static void LoadDescriptors(const std::string &_paths);
    };

    /// \brief Static message registration macro
    ///
    /// Use this macro to register messages.
    /// \param[in] _msgtype Message type name.
    /// \param[in] _classname Class name for message.
    #define GZ_REGISTER_STATIC_MSG(_msgtype, _classname) \
    GZ_MSGS_VISIBLE \
    gz::msgs::Factory::MessagePtr New##_classname() \
    { \
      return std::unique_ptr<gz::msgs::_classname>(\
          new gz::msgs::_classname); \
    } \
    class GZ_MSGS_VISIBLE GzMsg##_classname \
    { \
      public: GzMsg##_classname() \
      { \
        gz::msgs::Factory::Register(_msgtype, New##_classname);\
      } \
    }; \
    static GzMsg##_classname GzMessagesInitializer##_classname;
    }
  }
}
#endif
