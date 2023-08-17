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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146 4251)
#endif
#include <google/protobuf/text_format.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "DynamicFactory.hh"
#include "gz/msgs/MessageFactory.hh"
#include <gz/utils/ImplPtr.hh>

namespace gz::msgs
{

/////////////////////////////////////////////////
MessageFactory::MessageFactory():
  dynamicFactory(gz::utils::MakeUniqueImpl<gz::msgs::DynamicFactory>())
{
}

/////////////////////////////////////////////////
MessageFactory::~MessageFactory() = default;

/////////////////////////////////////////////////
void MessageFactory::Register(const std::string &_msgType,
                              FactoryFn _factoryfn)
{
  msgMap[_msgType] = _factoryfn;
}

/////////////////////////////////////////////////
MessageFactory::MessagePtr MessageFactory::New(
    const std::string &_msgType)
{
  std::string type;

  // Convert "gz.msgs." to "gz_msgs.".
  if (_msgType.find("gz_msgs.") == 0)
  {
    type = "gz.msgs." + _msgType.substr(8);
  }
  else if (_msgType.find(".gz_msgs.") == 0)
  {
    type = "gz.msgs." + _msgType.substr(9);
  }
  // Convert ".gz.msgs." to "gz_msgs.".
  else if (_msgType.find(".gz.msgs.") == 0)
  {
    type = "gz.msgs." + _msgType.substr(9);
  }
  else
  {
    type = _msgType;
  }

  if (msgMap.find(type) != msgMap.end())
  {
    // Create a new message if a FactoryFn has been assigned to the message type
    return msgMap[type]();
  }
  else
  {
    // Check if we have the message descriptor.
    return dynamicFactory->New(type);
  }
}

/////////////////////////////////////////////////
MessageFactory::MessagePtr MessageFactory::New(
    const std::string &_msgType, const std::string &_args)
{
  std::unique_ptr<google::protobuf::Message> msg = New(_msgType);
  if (msg)
  {
    google::protobuf::TextFormat::ParseFromString(_args, msg.get());
  }
  return msg;
}

/////////////////////////////////////////////////
void MessageFactory::Types(std::vector<std::string> &_types)
{
  _types.clear();

  // Return the list of all known message types.
  std::map<std::string, FactoryFn>::const_iterator iter;
  for (iter = msgMap.begin(); iter != msgMap.end(); ++iter)
  {
    _types.push_back(iter->first);
  }

  // Add the types loaded from descriptor files
  this->dynamicFactory->Types(_types);
}

/////////////////////////////////////////////////
void MessageFactory::LoadDescriptors(const std::string &_paths)
{
  dynamicFactory->LoadDescriptors(_paths);
}

}  // namespace gz::msgs
