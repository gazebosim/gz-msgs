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

namespace gz::msgs
{

/////////////////////////////////////////////////
MessageFactory::MessageFactory():
  dynamicFactory(std::make_unique<gz::msgs::DynamicFactory>())
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
int MessageFactory::RegisterCollection(FactoryFnCollection &_functions)
{
  int registered = 0;
  for (auto it : _functions) {
    this->Register(it.first, it.second);
    registered++;
  }
  return registered;
}

/////////////////////////////////////////////////
MessageFactory::MessagePtr MessageFactory::New(
    const std::string &_msgType)
{
  if (msgMap.find(_msgType) != msgMap.end())
  {
    // Create a new message if a FactoryFn has been assigned to the message type
    return msgMap[_msgType]();
  }
  else
  {
    // Check if we have the message descriptor.
    return dynamicFactory->New(_msgType);
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
}

/////////////////////////////////////////////////
void MessageFactory::LoadDescriptors(const std::string &_paths)
{
  dynamicFactory->LoadDescriptors(_paths);
}

}  // namespace gz::msgs
