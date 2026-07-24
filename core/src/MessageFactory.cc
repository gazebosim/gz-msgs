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

#include <mutex>
#include <unordered_set>

#include <google/protobuf/text_format.h>

#include "DynamicFactory.hh"
#include "gz/msgs/MessageFactory.hh"
#include <gz/utils/ImplPtr.hh>

static constexpr const char * kGzMsgsPrefix = "gz.msgs.";

namespace gz::msgs
{

/// \brief Private implementation of MessageFactory.
class MessageFactory::Implementation
{
  /// \brief Protects every member below, as well as the dynamic factory
  /// reached through dynamicFactory, which is not thread safe on its own.
  public: std::mutex mutex;

  /// \brief A list of registered message types.
  public: FactoryFnCollection msgMap;

  /// \brief Factory for messages built at runtime from loaded descriptors.
  public: std::unique_ptr<gz::msgs::DynamicFactory> dynamicFactory;

  /// \brief Get the dynamic factory, constructing it on first use.
  /// Construction scans and parses every descriptor file reachable from
  /// the GZ_DESCRIPTOR_PATH environment variable and the install share
  /// directory, so it is deferred until a dynamic lookup needs it.
  /// The caller must hold mutex.
  /// \return Reference to the dynamic factory.
  public: gz::msgs::DynamicFactory &EnsureDynamicFactory();
};

/////////////////////////////////////////////////
gz::msgs::DynamicFactory &MessageFactory::Implementation::EnsureDynamicFactory()
{
  if (!this->dynamicFactory)
    this->dynamicFactory = std::make_unique<gz::msgs::DynamicFactory>();
  return *this->dynamicFactory;
}

/////////////////////////////////////////////////
MessageFactory::MessageFactory():
  dataPtr(gz::utils::MakeUniqueImpl<Implementation>())
{
}

/////////////////////////////////////////////////
MessageFactory::~MessageFactory() = default;

/////////////////////////////////////////////////
void MessageFactory::Register(const std::string &_msgType,
                              FactoryFn _factoryfn)
{
  std::lock_guard<std::mutex> lock(this->dataPtr->mutex);
  this->dataPtr->msgMap[_msgType] = _factoryfn;
}

/////////////////////////////////////////////////
MessageFactory::MessagePtr MessageFactory::New(
    const std::string &_msgType)
{
  std::string type;

  // Convert "gz_msgs." prefix
  if (_msgType.find("gz_msgs.") == 0)
  {
    type = kGzMsgsPrefix + _msgType.substr(8);
  }
  // Convert ".gz.msgs." prefix
  else if (_msgType.find(".gz.msgs.") == 0)
  {
    type = kGzMsgsPrefix + _msgType.substr(9);
  }
  // Convert ".gz_msgs." prefix
  else if (_msgType.find(".gz_msgs.") == 0)
  {
    type = kGzMsgsPrefix + _msgType.substr(9);
  }
  else
  {
    type = _msgType;
  }

  FactoryFn factoryFn;
  {
    std::lock_guard<std::mutex> lock(this->dataPtr->mutex);
    if (auto it = this->dataPtr->msgMap.find(type);
        it != this->dataPtr->msgMap.end())
    {
      // Copy the factory function so that it can be invoked outside the
      // lock, allowing a factory function to call back into this class.
      factoryFn = it->second;
    }
    else
    {
      // Create a new message via dynamic descriptors
      return this->dataPtr->EnsureDynamicFactory().New(type);
    }
  }

  // Create a new message via FactoryFn
  if (factoryFn) return factoryFn();
  return nullptr;
}

/////////////////////////////////////////////////
MessageFactory::MessagePtr MessageFactory::New(
    const std::string &_msgType, const std::string &_args)
{
  std::unique_ptr<google::protobuf::Message> msg = New(_msgType);
  if (msg)
  {
    if (!google::protobuf::TextFormat::ParseFromString(_args, msg.get()))
    {
      // The user-provided string was invalid,
      // return nullptr rather than an empty message.
      msg.reset();
    }
  }
  return msg;
}

/////////////////////////////////////////////////
void MessageFactory::Types(std::vector<std::string> &_types)
{
  _types.clear();

  std::lock_guard<std::mutex> lock(this->dataPtr->mutex);

  // Add the types loaded from descriptor files
  std::vector<std::string> dynTypes;
  this->dataPtr->EnsureDynamicFactory().Types(dynTypes);

  // Use set to remove duplicates
  std::unordered_set<std::string> typesSet(dynTypes.begin(), dynTypes.end());

  // Return the list of all known message types.
  for (const auto &[typeName, factoryFn] : this->dataPtr->msgMap)
  {
    typesSet.insert(typeName);
  }

  _types.reserve(typesSet.size());
  std::copy(typesSet.begin(), typesSet.end(), std::back_inserter(_types));
}

/////////////////////////////////////////////////
void MessageFactory::LoadDescriptors(const std::string &_paths)
{
  std::lock_guard<std::mutex> lock(this->dataPtr->mutex);
  this->dataPtr->EnsureDynamicFactory().LoadDescriptors(_paths);
}

}  // namespace gz::msgs
