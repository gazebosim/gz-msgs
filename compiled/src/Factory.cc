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

#include "gz/msgs/Factory.hh"
#include "gz/msgs/MessageFactory.hh"
#include <gz/utils/NeverDestroyed.hh>

using namespace gz;
using namespace msgs;


gz::msgs::MessageFactory& GetFactoryInstance() {
  static gz::utils::NeverDestroyed<MessageFactory> instance;
  return instance.Access();
}

/////////////////////////////////////////////////
void Factory::Register(const std::string &_msgType,
                       Factory::FactoryFn _factoryfn)
{
  GetFactoryInstance().Register(_msgType, _factoryfn);
}

/////////////////////////////////////////////////
std::unique_ptr<google::protobuf::Message> Factory::New(
    const std::string &_msgType)
{
  return GetFactoryInstance().New(_msgType);
}

/////////////////////////////////////////////////
std::unique_ptr<google::protobuf::Message> Factory::New(
    const std::string &_msgType, const std::string &_args)
{
  return GetFactoryInstance().New(_msgType, _args);
}

/////////////////////////////////////////////////
void Factory::Types(std::vector<std::string> &_types)
{
  GetFactoryInstance().Types(_types);
}

/////////////////////////////////////////////////
void Factory::LoadDescriptors(const std::string &_paths)
{
  GetFactoryInstance().LoadDescriptors(_paths);
}
