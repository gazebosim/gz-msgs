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
 * */
#include <google/protobuf/descriptor.h>
#include <iostream>
#include "ignition/msgs/msgs.hh"

#ifdef _MSC_VER
# pragma warning(disable: 4503)
#endif

using namespace ignition;
using namespace msgs;

//////////////////////////////////////////////////
void cmdMsgInfo(const char *_msg)
{
  if (_msg)
  {
    auto msg = ignition::msgs::Factory::New(_msg);
    if (msg)
    {
      auto descriptor = msg->GetDescriptor();
      auto fileDescriptor = descriptor->file();
      std::cout << "Name: " << descriptor->full_name() << std::endl;
      std::cout << "File: " << fileDescriptor->name() << std::endl << std::endl;

      std::cout << descriptor->DebugString() << std::endl;
    }
    else
      std::cerr << "Unable to create message of type[" << _msg << "]\n";
  }
  else
  {
    std::cerr << "Messsage type is null\n";
  }
}

//////////////////////////////////////////////////
void cmdMsgList()
{
  std::vector<std::string> types;
  ignition::msgs::Factory::Types(types);

  for (auto const &type : types)
    std::cout << type << std::endl;
}

//////////////////////////////////////////////////
char *ignitionMsgsVersion()
{
  int majorVersion = IGNITION_MSGS_MAJOR_VERSION;
  int minorVersion = IGNITION_MSGS_MINOR_VERSION;
  int patchVersion = IGNITION_MSGS_PATCH_VERSION;

  return ign_strdup((std::to_string(majorVersion) + "." +
                     std::to_string(minorVersion) + "." +
                     std::to_string(patchVersion)).c_str());
}
