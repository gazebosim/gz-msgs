/*
 * Copyright (C) 2023 Open Source Robotics Foundation
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

#include <algorithm>
#include <fstream>
#include <filesystem>
#include <vector>

#include "DynamicFactory.hh"
#include "gz/utils/Environment.hh"

#include <gz/msgs/InstallationDirectories.hh>

namespace {
constexpr const char * kDescriptorEnv = "GZ_DESCRIPTOR_PATH";
#ifdef _WIN32
constexpr char kEnvironmentVariableSeparator = ';';
#else
constexpr char kEnvironmentVariableSeparator = ':';
#endif

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
}  // namespace

namespace gz::msgs {

//////////////////////////////////////////////////
DynamicFactory::DynamicFactory()
{
  // Try to get the list of paths from an environment variable.
  std::string descPaths;
  if (gz::utils::env(kDescriptorEnv, descPaths)) {
    // Load all the descriptors found in the paths set with GZ_DESCRIPTOR_PATH.
    this->LoadDescriptors(descPaths);
  }
  else
  {
    // Load descriptors from the global share path
    this->LoadDescriptors((std::filesystem::path(
      gz::msgs::getInstallPrefix()) / "share" / "gz" / "protos").string());
  }
}

//////////////////////////////////////////////////
void DynamicFactory::LoadDescriptors(const std::string &_paths)
{
  if (_paths.empty())
    return;

  std::cout << "DynamicFactory::LoadDescriptors(" << _paths << "\n";

  // Split all the directories containing .desc files.
  std::vector<std::string> descDirs =
    split(_paths, kEnvironmentVariableSeparator);


  for (const std::string &descDir : descDirs)
  {
    for (auto const &dirIter : std::filesystem::directory_iterator{descDir})
    {
      // Ignore files without the .desc extension.
      if (dirIter.path().extension() != ".desc" &&
          dirIter.path().extension() != ".gz_desc")
        continue;

      std::ifstream ifs(dirIter.path().string(), std::ifstream::in);
      if (!ifs.is_open())
      {
        std::cerr << "DynamicFactory(): Unable to open ["
                  << dirIter.path() << "]"
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
        // If the descriptor already exists in the database, then skip it.
        // This may happen as gz_desc files can potentially contain the
        // transitive message definitions
        google::protobuf::FileDescriptorProto checkDescriptorProto;
        if (this->db.FindFileByName(
          fileDescriptorProto.name(), &checkDescriptorProto))
        {
          continue;
        }

        if (!static_cast<bool>(pool.BuildFile(fileDescriptorProto)))
        {
          std::cerr << "DynamicFactory(). Unable to place descriptors from ["
                    << dirIter.path()
                    << "] in the descriptor pool" << std::endl;
        }

        this->db.Add(fileDescriptorProto);
      }
    }
  }

}

//////////////////////////////////////////////////
void DynamicFactory::Types(std::vector<std::string> &_types)
{
  std::vector<std::string> messages;
  this->db.FindAllMessageNames(&messages);
  std::copy(messages.begin(), messages.end(), std::back_inserter(_types));
}

//////////////////////////////////////////////////
DynamicFactory::MessagePtr DynamicFactory::New(const std::string &_msgType)
{
  // Shortcut if the type has been already registered.
  auto messageIt = dynamicMsgMap.find(_msgType);
  if (messageIt != dynamicMsgMap.end())
    return messageIt ->second();

  // Nothing to do if we don't know about this type in the descriptor map.
  const auto *descriptor = pool.FindMessageTypeByName(_msgType);
  if (!static_cast<bool>(descriptor))
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
}  // namespace gz::msgs
