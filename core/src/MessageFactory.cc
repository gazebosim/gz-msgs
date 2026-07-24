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
  /// \brief A list of registered message types.
  public: FactoryFnCollection msgMap;

  /// \brief Factory for messages built at runtime from loaded descriptors.
  public: std::unique_ptr<gz::msgs::DynamicFactory> dynamicFactory =
      std::make_unique<gz::msgs::DynamicFactory>();
};

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

  if (auto it = this->dataPtr->msgMap.find(type);
      it != this->dataPtr->msgMap.end())
  {
    // Create a new message via FactoryFn
    return it->second();
  }

  // Create a new message via dynamic descriptors
  return this->dataPtr->dynamicFactory->New(type);
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

  // Add the types loaded from descriptor files
  std::vector<std::string> dynTypes;
  this->dataPtr->dynamicFactory->Types(dynTypes);

  // Use set to remove duplicates
  std::unordered_set<std::string> typesSet(dynTypes.begin(), dynTypes.end());

  // Return the list of all known message types.
  for (const auto &[typeName, factoryFn] : this->dataPtr->msgMap)
  {
    typesSet.insert(typeName);
  }

  std::copy(typesSet.begin(), typesSet.end(), std::back_inserter(_types));
}

/////////////////////////////////////////////////
void MessageFactory::LoadDescriptors(const std::string &_paths)
{
  this->dataPtr->dynamicFactory->LoadDescriptors(_paths);
}

}  // namespace gz::msgs
