/*
 * Copyright (C) 2012-2013 Open Source Robotics Foundation
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

#ifndef _IGNITION_MSGS_FACTORY_HH_
#define _IGNITION_MSGS_FACTORY_HH_

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <google/protobuf/message.h>

namespace ignition
{
  namespace messages
  {
    /// \def FactoryFn
    /// \brief Prototype for message factory generation
    typedef std::shared_ptr<google::protobuf::Message> (*FactoryFn) ();

    /// \class Factory Factory.hh ignition/messages.hh
    /// \brief A factory that generates protobuf message based on a string
    /// type.
    class Factory
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
      public: static std::shared_ptr<google::protobuf::Message> New(
                  const std::string &_msgType);

      /// \brief Get all the message types
      /// \param[out] _types Vector of strings of the message types.
      public: static void GetTypes(std::vector<std::string> &_types);

      /// \brief A list of registered message types
      private: static std::map<std::string, FactoryFn> *msgMap;
    };


    /// \brief Static message registration macro
    ///
    /// Use this macro to register messages.
    /// \param[in] _msgtype Message type name.
    /// \param[in] _classname Class name for message.
    #define IGN_REGISTER_STATIC_MSG(_msgtype, _classname) \
    std::shared_ptr<google::protobuf::Message> New##_classname() \
    { \
      return std::shared_ptr<ignition::messages::_classname>(\
          new ignition::messages::_classname); \
    } \
    class IgnMsg##_classname \
    { \
      public: IgnMsg##_classname() \
      { \
        ignition::messages::Factory::Register(_msgtype, New##_classname);\
      } \
    }; \
    static IgnMsg##_classname IgnitionMessagesInitializer;
  }
}
#endif
