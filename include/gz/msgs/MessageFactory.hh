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
#ifndef GZ_MSGS_MESSAGE_FACTORY_HH_
#define GZ_MSGS_MESSAGE_FACTORY_HH_

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "gz/msgs/config.hh"
#include "gz/msgs/Export.hh"
#include "gz/msgs/detail/dynamic_message_cast.hh"

namespace gz::msgs {
  /// Forward declarations
  class DynamicFactory;

  // Inline bracket to help doxygen filtering.
  inline namespace GZ_MSGS_VERSION_NAMESPACE {

  class GZ_MSGS_VISIBLE MessageFactory
  {
    public: using Message = google::protobuf::Message;
    public: using MessagePtr = std::unique_ptr<Message>;
    public: using FactoryFn = std::function<MessagePtr(void)>;

    public: MessageFactory();

    /// \brief Register a message.
    /// \param[in] _msgType Type of message to register.
    /// \param[in] _factoryfn Function that generates the message.
    public: void Register(const std::string &_msgType, FactoryFn _factoryFn);

    /// \brief Create a new instance of a message.
    /// \param[in] _msgType Type of message to create.
    /// \return Pointer to a google protobuf message. Null if the message
    /// type could not be handled.
    public: template<typename T>
            std::unique_ptr<T> New(const std::string &_msgType)
            {
              return detail::dynamic_message_cast<T>(New(_msgType));
            }

    /// \brief Create a new instance of a message.
    /// \param[in] _msgType Type of message to create.
    /// \param[in] _args Message arguments. This will populate the message.
    /// \return Pointer to a google protobuf message. Null if the message
    /// type could not be handled.
    public: template<typename T>
            std::unique_ptr<T> New(const std::string &_msgType,
                const std::string &_args)
            {
              return detail::dynamic_message_cast<T>(New(_msgType, _args));
            }

    /// \brief Create a new instance of a message.
    /// \param[in] _msgType Type of message to create.
    /// \return Pointer to a google protobuf message. Null if the message
    /// type could not be handled.
    public: MessagePtr New(const std::string &_msgType);

    /// \brief Create a new instance of a message.
    /// \param[in] _msgType Type of message to create.
    /// \param[in] _args Message arguments. This will populate the message.
    /// \return Pointer to a google protobuf message. Null if the message
    /// type could not be handled.
    public: MessagePtr New(
                const std::string &_msgType, const std::string &_args);

    /// \brief Get all the message types
    /// \param[out] _types Vector of strings of the message types.
    public: void Types(std::vector<std::string> &_types);

    /// \brief Load a collection of descriptor .desc files.
    /// \param[in] _paths A set of directories containing .desc decriptor
    /// files. Each directory should be separated by ":".
    public: void LoadDescriptors(const std::string &_paths);

    /// \brief A list of registered message types
    private: std::map<std::string, FactoryFn> msgMap;

    private: std::unique_ptr<DynamicFactory> dynamicFactory;
  };
}
}  // namespace gz::msgs
#endif  // GZ_MSGS_MESSAGE_FACTORY_HH_
