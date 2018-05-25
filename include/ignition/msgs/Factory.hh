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
#ifndef IGNITION_MSGS_FACTORY_HH_
#define IGNITION_MSGS_FACTORY_HH_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4512 4127 4068 4244 4267 4251 4146)
#endif
#include <google/protobuf/message.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "ignition/msgs/config.hh"
#include "ignition/msgs/Export.hh"

namespace ignition
{
  namespace msgs
  {
    // Inline bracket to help doxygen filtering.
    inline namespace IGNITION_MSGS_VERSION_NAMESPACE {
    //
    /// \typedef FactoryFn
    /// \brief Prototype for message factory generation
    typedef std::unique_ptr<google::protobuf::Message> (*FactoryFn) ();

    /// \class Factory Factory.hh ignition/msgs.hh
    /// \brief A factory that generates protobuf message based on a string type.
    /// This class  will also try to load all Protobuf descriptors specified
    /// in the IGN_DESCRIPTOR_PATH environment variable on program start.
    class IGNITION_MSGS_VISIBLE Factory
    {
      /// \brief Register a message.
      /// \param[in] _msgType Type of message to register.
      /// \param[in] _factoryfn Function that generates the message.
      public: static void Register(const std::string &_msgType,
                                   FactoryFn _factoryfn);

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: template<typename T>
              static std::unique_ptr<T> New(const std::string &_msgType)
              {
                return std::unique_ptr<T>(
                    static_cast<T*>(New(_msgType).release()));
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
                return std::unique_ptr<T>(
                    static_cast<T*>(New(_msgType, _args).release()));
              }

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: static std::unique_ptr<google::protobuf::Message> New(
                  const std::string &_msgType);

      /// \brief Create a new instance of a message.
      /// \param[in] _msgType Type of message to create.
      /// \param[in] _args Message arguments. This will populate the message.
      /// \return Pointer to a google protobuf message. Null if the message
      /// type could not be handled.
      public: static std::unique_ptr<google::protobuf::Message> New(
                  const std::string &_msgType, const std::string &_args);

      /// \brief Get all the message types
      /// \param[out] _types Vector of strings of the message types.
      public: static void Types(std::vector<std::string> &_types);

      /// \brief Load a collection of descriptor .desc files.
      /// \param[in] _paths A set of directories containing .desc decriptor
      /// files. Each directory should be separated by ":".
      public: static void LoadDescriptors(const std::string &_paths);

      /// \brief A list of registered message types
      private: static std::map<std::string, FactoryFn> *msgMap;
    };

    /// \brief Static message registration macro
    ///
    /// Use this macro to register messages.
    /// \param[in] _msgtype Message type name.
    /// \param[in] _classname Class name for message.
    #define IGN_REGISTER_STATIC_MSG(_msgtype, _classname) \
    IGNITION_MSGS_VISIBLE \
    std::unique_ptr<google::protobuf::Message> New##_classname() \
    { \
      return std::unique_ptr<ignition::msgs::_classname>(\
          new ignition::msgs::_classname); \
    } \
    class IGNITION_MSGS_VISIBLE IgnMsg##_classname \
    { \
      public: IgnMsg##_classname() \
      { \
        ignition::msgs::Factory::Register(_msgtype, New##_classname);\
      } \
    }; \
    static IgnMsg##_classname IgnitionMessagesInitializer;
    }
  }
}
#endif
