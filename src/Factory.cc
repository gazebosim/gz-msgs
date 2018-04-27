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
#include <iostream>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/text_format.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "ignition/msgs/Factory.hh"

using namespace ignition;
using namespace msgs;

std::map<std::string, FactoryFn> *Factory::msgMap = NULL;

class IgnMultiFileErrorCollector
  : public google::protobuf::compiler::MultiFileErrorCollector
{
  void AddError(const std::string& filename, int line, int column,
               const std::string& message)
  {
    std::cerr << "[" << filename << "] (" << line << ":" << column << "): "
              << message << std::endl;
  }
};

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

  // caguero - Testing.
  const char *ignProtoPath = std::getenv("IGN_PROTO_PATH");
  const char *ignDescPath = std::getenv("IGN_DESCRIPTOR_PATH");
  if (ignProtoPath)
  {

    // std::cout << "IGN_PROTO_PATH [" << ignProtoPath << "]" << std::endl;

    // Option A - Using .proto
    static google::protobuf::compiler::DiskSourceTree sourceTree;
    sourceTree.MapPath("", ignProtoPath);
    static IgnMultiFileErrorCollector errorMist;
    static google::protobuf::compiler::Importer importer(
      &sourceTree, &errorMist);

    importer.Import("stringmsg.proto");

    const google::protobuf::DescriptorPool* pool = importer.pool();
    static google::protobuf::DynamicMessageFactory dmf;
    const google::protobuf::Descriptor* desc =
      pool->FindMessageTypeByName(_msgType);
    const google::protobuf::Message* msgProto = dmf.GetPrototype(desc);
    msg.reset(msgProto->New());
  }
  else if (ignDescPath)
  {

    // std::cout << "IGN_DESCRIPTOR_PATH [" << ignDescPath << "]" << std::endl;

    // Option B - Using .desc.
    std::ifstream ifs(ignDescPath);
    google::protobuf::FileDescriptorSet fileDescriptorSet;
    fileDescriptorSet.ParseFromIstream(&ifs);

    const google::protobuf::DescriptorPool *compiledPool =
      google::protobuf::DescriptorPool::generated_pool();
    if (!compiledPool)
    {
      std::cerr  << "compiled pool is nullptr" << std::endl;
      return nullptr;
    }

    const google::protobuf::Descriptor *desc =
      compiledPool->FindMessageTypeByName(_msgType);

    if (desc)
    {
      msg.reset(google::protobuf::MessageFactory::generated_factory()->
        GetPrototype(desc)->New());
    }

    static google::protobuf::DescriptorPool pool(compiledPool);
    static google::protobuf::DynamicMessageFactory dynamicMessageFactory(&pool);

    for (const auto &fileDescriptorProto : fileDescriptorSet.file())
    {
      const google::protobuf::FileDescriptor *fileDescriptor =
        pool.BuildFile(fileDescriptorProto);
      if (fileDescriptor == nullptr)
        continue;

      const google::protobuf::Descriptor *descriptor =
        pool.FindMessageTypeByName(_msgType);

      if (descriptor == nullptr)
      {
        std::cerr << "Descriptor is NULL" << std::endl;
        continue;
      }

      msg.reset(dynamicMessageFactory.GetPrototype(descriptor)->New());
      break;
    }
  }
  // end caguero - Testing.

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
