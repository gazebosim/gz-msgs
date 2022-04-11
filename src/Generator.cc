/*
 * Copyright 2016 Open Source Robotics Foundation
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
#pragma warning(disable: 4100 4512 4127 4068 4244 4267 4251 4146)
#endif

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Generator.hh"

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

/////////////////////////////////////////////////
void replaceAll(std::string &_src, const std::string &_oldValue,
  const std::string &_newValue)
{
    for (size_t i = 0; (i = _src.find(_oldValue, i)) != std::string::npos;)
    {
      _src.replace(i, _oldValue.length(), _newValue);
      i += _newValue.length() - _oldValue.length() + 1;
    }
}

/////////////////////////////////////////////////
Generator::Generator(const std::string &/*_name*/)
{
}

/////////////////////////////////////////////////
Generator::~Generator()
{
}

/////////////////////////////////////////////////
bool Generator::Generate(const FileDescriptor *_file,
                               const std::string &/*_parameter*/,
                               OutputDirectory *_generatorContext,
                               std::string * /*_error*/) const
{
  std::string headerFilename = _file->name();
  std::string delim = ".proto";
  size_t pos = headerFilename.rfind(delim);
  headerFilename.replace(pos, delim.size(), ".pb.h");

  std::string sourceFilename = _file->name();
  pos = sourceFilename.rfind(delim);
  sourceFilename.replace(pos, delim.size(), ".pb.cc");

  // Inject code in the auto-generated header immediately following
  // the #include <google/protobuf/*.h> calls
  {
    std::unique_ptr<io::ZeroCopyOutputStream> output(
        _generatorContext->OpenForInsert(headerFilename, "includes"));
    io::Printer printer(output.get(), '$');

    // Suppress expected warnings
    printer.Print("#ifndef _MSC_VER\n", "name", "includes");
    printer.Print("#pragma GCC system_header\n", "name", "includes");
    printer.Print("#else\n", "name", "includes");
    printer.Print("#pragma warning(push)\n", "name", "includes");
    printer.Print("#pragma warning(disable: 4244 4267 4100 4244 4512",
        "name", "includes");
    printer.Print(" 4127 4068 4275 4251)\n", "name", "includes");
    printer.Print("#endif\n", "name", "includes");

    // Include sys/sysmacros.h to prevent warnings about "major" and "minor"
    // defines. Major and minor are used in the version.proto file.
    printer.Print("#ifdef __linux__\n", "name", "includes");
    printer.Print("#include <sys/sysmacros.h>\n", "name", "include");
    printer.Print("#endif\n", "name", "includes");

    // Add the <memory> header so that we can define std::unique_ptr
    // and std::shared_ptr types for our message later on
    printer.Print("#include <memory>\n", "name", "includes");

    // Add the Export header so that we can apply visibility macros
    // to the messages
    printer.Print("#include <ignition/msgs/Export.hh>\n", "name",
      "includes");
  }

  // Inject code in the auto-generated source files immediately following
  // the #include <google/protobuf*.h> calls.
  {
    std::unique_ptr<io::ZeroCopyOutputStream> output(
        _generatorContext->OpenForInsert(sourceFilename, "includes"));
    io::Printer printer(output.get(), '$');

    // Add the ign-msgs Factory header
    printer.Print("#include \"ignition/msgs/Factory.hh\"\n", "name",
                  "includes");

    // Suppress warnings
    printer.Print("#ifndef _MSC_VER\n", "name", "includes");
    printer.Print("#pragma GCC diagnostic ignored \"-Wshadow\"\n", "name",
                  "includes");
    printer.Print("#pragma GCC diagnostic ignored \"-Wfloat-equal\"\n", "name",
                  "includes");
    printer.Print("#pragma GCC diagnostic ignored \"-Wunused-parameter\"\n",
        "name", "includes");
    printer.Print(
        "#pragma GCC diagnostic ignored \"-Wdeprecated-declarations\"\n",
        "name", "includes");
    printer.Print("#else\n", "name", "includes");
    printer.Print("#pragma warning(disable: 4244 4267 4100 4244 4512",
                  "name", "includes");
    printer.Print(" 4127 4068)\n", "name", "includes");
    printer.Print("#endif\n", "name", "includes");

    // Call the IGN_REGISTER_STATIC_MSG macro
    std::string factory = "IGN_REGISTER_STATIC_MSG(\"ign_msgs.";
    factory += _file->message_type(0)->name() + "\", " +
      _file->message_type(0)->name() +")";
    printer.Print(factory.c_str(), "name", "includes");
  }

  // Inject code in the auto-generated header files immediately before closing
  // the namespace that the messages are in
  {
    std::unique_ptr<io::ZeroCopyOutputStream> output(
        _generatorContext->OpenForInsert(headerFilename, "namespace_scope"));
    io::Printer printer(output.get(), '$');

    // Define std::unique_ptr types for our messages
    std::string ptrTypes = "typedef std::unique_ptr<"
      + _file->message_type(0)->name() + "> "
      + _file->message_type(0)->name() + "UniquePtr;\n";

    // Define const std::unique_ptr types for our messages
    ptrTypes += "typedef std::unique_ptr<const "
      + _file->message_type(0)->name() + "> Const"
      + _file->message_type(0)->name() + "UniquePtr;\n";

    // Define std::shared_ptr types for our messages
    ptrTypes += "typedef std::shared_ptr<"
      + _file->message_type(0)->name() + "> "
      + _file->message_type(0)->name() + "SharedPtr;\n";

    // Define const std::shared_ptr types for our messages
    ptrTypes += "typedef std::shared_ptr<const "
      + _file->message_type(0)->name() + "> Const"
      + _file->message_type(0)->name() + "SharedPtr;\n";

    printer.Print(ptrTypes.c_str(), "name", "namespace_scope");
  }

  // Pop the warning suppression stack for MSVC
  {
    std::unique_ptr<io::ZeroCopyOutputStream> output(
      _generatorContext->OpenForInsert(headerFilename, "global_scope"));
    io::Printer printer(output.get(), '$');

    std::string warningPop = "#ifdef _MSC_VER\n";
    warningPop += "#pragma warning(pop)\n";
    warningPop += "#endif";

    printer.Print(warningPop.c_str(), "name", "global_scope");
  }

  return true;
}
}
}
}
}
