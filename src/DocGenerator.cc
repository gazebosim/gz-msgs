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
#include <iostream>
#include <fstream>
#include <vector>
#include <gflags/gflags.h>
#include <google/protobuf/compiler/importer.h>
#include <ignition/common/Filesystem.hh>

// Gflag command line argument definitions
DEFINE_string(d, "", "Directory that contains protobuf files.");

using namespace ignition;

class ErrorCollector :
  public google::protobuf::compiler::MultiFileErrorCollector
{
  void AddError(const std::string &_filename, int _line, int _column,
                const std::string &_message)
  {
    std::cout << "Error[" << _filename << ":" << _line << ","
               << _column << "] " << _message << std::endl;
  }
};

class Doc
{
  public: void Write()
  {
    std::ofstream out("/tmp/p.html");
    out << "<html>\n";

    for (const std::pair<std::string,
         google::protobuf::DescriptorProto> &msg : this->messages)
    {
      out << "<h3>" << msg.second.name() << " in "
        << messagesLoc[msg.first] << "</h3>\n";

      out << "<table>";
      out << "<thead><tr>"
          << "<th>Name</th>"
          << "<th>Type</th>"
          << "<th>Label</th>"
          << "<th>Description</th>"
          << "<th>Number</th>"
          << "</tr></thead>";
      for (int fieldI = 0; fieldI < msg.second.field_size(); ++fieldI)
      {
        out << "<tr>";
        const google::protobuf::FieldDescriptorProto &field =
          msg.second.field(fieldI);
        out << "<td>" << field.name() << "</td>"
            << "<td>" << field.type() << "</td>";

        out << "<td>";
        if (field.has_label())
        {
          switch (field.label())
          {
            default:
            case google::protobuf::FieldDescriptorProto_Label_LABEL_OPTIONAL:
              out << "optional";
              break;
            case google::protobuf::FieldDescriptorProto_Label_LABEL_REQUIRED:
              out << "required";
              break;
            case google::protobuf::FieldDescriptorProto_Label_LABEL_REPEATED:
              out << "repeated";
              break;
          }
        }
        out << "</td>";

        out << "<td>" << this->messagesLoc[msg.first] << ".4." << fieldI << "</td>"
            << "<td>" << field.number() << "</td>";
        out << "</tr>";
      }
      out << "</table>\n";
    }
    out << "</html>\n";
  }

  public: std::map<std::string, google::protobuf::DescriptorProto> messages;
  public: std::map<std::string, std::string> messagesLoc;
  public: std::map<std::string, std::string> messagesPath;
};

int main(int _argc, char **_argv)
{
  // Parse command line
  gflags::ParseCommandLineNonHelpFlags(&_argc, &_argv, true);

  if (FLAGS_d.empty())
  {
    std::cerr << "Missing directory (-d)\n";
    return -1;
  }

  if (!common::isDirectory(FLAGS_d))
  {
    std::cerr << "Not a directory[" << FLAGS_d << "]\n";
    return -1;
  }

  google::protobuf::compiler::DiskSourceTree sourceTree;
  sourceTree.MapPath("", "/home/nkoenig/work/ignition/ign-msgs/proto/ignition/msgs");
  sourceTree.MapPath("ignition/msgs", "/home/nkoenig/work/ignition/ign-msgs/proto/ignition/msgs");

  ErrorCollector errorCollector;

  Doc doc;

  std::map<std::string, std::string> allComments;
  std::vector<std::string> protoFilenames;
  for (common::DirIter dirIter(FLAGS_d);
       dirIter != common::DirIter(); ++dirIter)
  {
    if ((*dirIter).find(".proto") != (*dirIter).size() - 6)
      continue;

    google::protobuf::compiler::Importer importer(&sourceTree,
        &errorCollector);

    std::string baseName = common::basename(*dirIter);
    protoFilenames.push_back(baseName);

    const google::protobuf::FileDescriptor *fileDescriptor =
      importer.Import(baseName);

    google::protobuf::FileDescriptorProto fileDescriptorProto;
    fileDescriptor->CopySourceCodeInfoTo(&fileDescriptorProto);
    const google::protobuf::SourceCodeInfo &sci = fileDescriptorProto.source_code_info();
    std::cout << baseName << " Size[" << sci.location_size() << "]\n";
    for (int locI = 0; locI < sci.location_size(); ++locI)
    {
      const google::protobuf::SourceCodeInfo_Location &scil  = sci.location(locI);
      if (!scil.leading_comments().empty() || !scil.trailing_comments().empty())
      {
        std::string path = baseName;
        for (int pathI = 0; pathI < scil.path_size(); ++pathI)
        {
          path += "." + std::to_string(scil.path(pathI));
        }

        std::cout << "[" << path << "] " << scil.leading_comments() << ":" << scil.trailing_comments() << std::endl;
      }
    }

    // message_type = 4;
    // nested_type = 3;
    // field_type = 2;
    std::cout << "\n=====================================================\n";
    for (int msgType = 0; msgType < fileDescriptor->message_type_count();
         ++msgType)
    {
      const google::protobuf::Descriptor *descriptor =
        fileDescriptor->message_type(msgType);
      std::cout << "Descriptor Index[" << descriptor->index() << "]\n";
/*
      google::protobuf::SourceLocation sourceLocation;
      descriptor->GetSourceLocation(&sourceLocation);

      std::string comments = sourceLocation.leading_comments +
                             sourceLocation.trailing_comments;
      std::cout << "* " << descriptor->name() << std::endl;
      std::cout << "    " << comments << std::endl;

      for (int fieldI = 0; fieldI < descriptor->field_size(); ++fieldI)
      {
      }
      */

      descriptor->CopyTo(&(doc.messages[descriptor->name()]));
      doc.messagesLoc[descriptor->name()] = baseName;
      doc.messagesPath[descriptor->name()] = baseName + ".4." +
        std::to_string(msgType);
    }
  }

  doc.Write();

  return 0;
}
