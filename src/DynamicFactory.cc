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

#include <fstream>
#include <filesystem>

#include "DynamicFactory.hh"

using namespace gz;
using namespace msgs;

//////////////////////////////////////////////////
/// \brief split at a one character delimiter to get a vector of something
/// \param[in] _orig The string to split
/// \param[in] _delim a character to split the string at
/// \returns vector of split pieces of the string excluding the delimiter
std::vector<std::string> split(const std::string &_orig, char _delim)
{
  std::vector<std::string> pieces;
  size_t pos1 = 0;
  size_t pos2 = _orig.find(_delim);
  while (pos2 != std::string::npos)
  {
    pieces.push_back(_orig.substr(pos1, pos2-pos1));
    pos1 = pos2+1;
    pos2 = _orig.find(_delim, pos2+1);
  }
  pieces.push_back(_orig.substr(pos1, _orig.size()-pos1));
  return pieces;
}

//////////////////////////////////////////////////
DynamicFactory::DynamicFactory()
{
  // Try to get the list of paths from an environment variable.
  const char *descPaths = std::getenv("GZ_DESCRIPTOR_PATH");

  // Load all the descriptors found in the paths set with GZ_DESCRIPTOR_PATH.
  this->LoadDescriptors(descPaths);
}

//////////////////////////////////////////////////
void DynamicFactory::LoadDescriptors(const std::string &_paths)
{
  if (_paths.empty())
    return;

  // Split all the directories containing .desc files.
  std::vector<std::string> descDirs = split(_paths, ':');

  for (const std::string &descDir : descDirs)
  {
    for (auto const &dirIter : std::filesystem::directory_iterator{descDir})
    {
      // Ignore files without the .desc extension.
      if (dirIter.path().extension() != ".desc")
        continue;

      std::ifstream ifs(dirIter.path().string(), std::ifstream::in);
      if (!ifs.is_open())
      {
        std::cerr << "DynamicFactory(): Unable to open [" << dirIter.path() << "]"
                  << std::endl;
        continue;
      }

      google::protobuf::FileDescriptorSet fileDescriptorSet;
      if (!fileDescriptorSet.ParseFromIstream(&ifs))
      {
        std::cerr << "DynamicFactory(): Unable to parse descriptor set from ["
                  << dirIter.path() << "]" << std::endl;
        continue;
      }

      for (const google::protobuf::FileDescriptorProto &fileDescriptorProto :
           fileDescriptorSet.file())
      {
        if (!pool.BuildFile(fileDescriptorProto))
        {
          std::cerr << "DynamicFactory(). Unable to place descriptors from ["
                    << dirIter.path() << "] in the descriptor pool" << std::endl;
        }
      }
    }
  }
}

//////////////////////////////////////////////////
DynamicFactory::MessagePtr DynamicFactory::New(const std::string &_msgType)
{
  auto msgType = _msgType;

  // Shortcut if the type has been already registered.
  auto message_it = dynamicMsgMap.find(msgType);
  if (message_it != dynamicMsgMap.end())
    return message_it ->second();

  // Nothing to do if we don't know about this type in the descriptor map.
  auto descriptor = pool.FindMessageTypeByName(msgType);
  if (!descriptor)
    return nullptr;

  google::protobuf::Message *msgPtr(
      dynamicMessageFactory.GetPrototype(descriptor)->New());

  // Create the lambda for registration purposes.
  auto f = [msgPtr]() -> MessagePtr
  {
    MessagePtr ptr(msgPtr->New());
    return ptr;
  };

  // Register the new type for the future.
  dynamicMsgMap[_msgType] = f;

  return f();
}
