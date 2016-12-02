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

#include <ignition/msgs.hh>

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  // Case #1.
  //ignition::msgs::StringMsg msg;
  //std::string type = msg.GetTypeName();

  // Case #2.
  std::string type = "ignition.msgs.StringMsg";
  std::cout << "Type: [" << type << "]" << std::endl;

  const google::protobuf::Descriptor *desc =
    google::protobuf::DescriptorPool::generated_pool()
      ->FindMessageTypeByName(type);
  if (!desc)
  {
    std::cerr << "Unable to find descriptor [" << type << "]"
              << std::endl;
    return -1;
  }
  else
    std::cout << "Descriptor found" << std::endl;

  return 0;
}
