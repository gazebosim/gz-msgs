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
#include <google/protobuf/text_format.h>
#include "ignition/msgs/Factory.hh"

using namespace ignition;
using namespace msgs;

std::map<std::string, FactoryFn> *Factory::msgMap = NULL;

/////////////////////////////////////////////////
void Factory::Register(const std::string &_msgType,
                       FactoryFn _factoryfn)
{
  // Create the msgMap if it's null
  if (!msgMap)
    msgMap = new std::map<std::string, FactoryFn>;

  (*msgMap)[_msgType] = _factoryfn;
}

/////////////////////////////////////////////////
std::unique_ptr<google::protobuf::Message> Factory::New(
    const std::string &_msgType)
{
  std::unique_ptr<google::protobuf::Message> msg;

  std::string type;
  // Convert "ignition.msgs." to "ign_msgs.".
  if (_msgType.find("ignition.msgs.") == 0)
  {
    type = "ign_msgs." + _msgType.substr(14);
  }
  // Convert ".ignition.msgs." to "ign_msgs.".
  else if (_msgType.find(".ignition.msgs.") == 0)
  {
    type = "ign_msgs." + _msgType.substr(15);
  }
  else
  {
    // Fix typenames that are missing "ign_msgs." at the beginning.
    if (_msgType.find("ign_msgs.") != 0)
      type = "ign_msgs.";
    type += _msgType;
  }

  // Create a new message if a FactoryFn has been assigned to the message
  // type
  if (msgMap->find(type) != msgMap->end())
    msg = ((*msgMap)[type]) ();

  return msg;
}

/////////////////////////////////////////////////
std::unique_ptr<google::protobuf::Message> Factory::New(
    const std::string &_msgType, const std::string &_args)
{
  auto msg = New(_msgType);
  if (msg)
  {
    google::protobuf::TextFormat::ParseFromString(_args, msg.get());
  }

  return msg;
}

/////////////////////////////////////////////////
void Factory::Types(std::vector<std::string> &_types)
{
  _types.clear();

  // Return the list of all known message types.
  std::map<std::string, FactoryFn>::const_iterator iter;
  for (iter = msgMap->begin(); iter != msgMap->end(); ++iter)
  {
    _types.push_back(iter->first);
  }
}
