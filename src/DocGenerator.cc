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

const char *customCss = R"customCss(

)customCss";

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
  public: std::string TypeName(const int _typeId) const
  {
    switch (_typeId)
    {
      case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
        return "double";
      case google::protobuf::FieldDescriptor::TYPE_FLOAT:
        return "float";
      case google::protobuf::FieldDescriptor::TYPE_INT64:
        return "int64";
      case google::protobuf::FieldDescriptor::TYPE_UINT64:
        return "uint64";
      case google::protobuf::FieldDescriptor::TYPE_INT32:
        return "int32";
      case google::protobuf::FieldDescriptor::TYPE_FIXED64:
        return "fixed64";
      case google::protobuf::FieldDescriptor::TYPE_FIXED32:
        return "fixed32";
      case google::protobuf::FieldDescriptor::TYPE_BOOL:
        return "bool";
      case google::protobuf::FieldDescriptor::TYPE_STRING:
        return "string";
      case google::protobuf::FieldDescriptor::TYPE_GROUP:
        return "group";
      case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
        return "message";
      case google::protobuf::FieldDescriptor::TYPE_BYTES:
        return "bytes";
      case google::protobuf::FieldDescriptor::TYPE_UINT32:
        return "uint32";
      case google::protobuf::FieldDescriptor::TYPE_ENUM:
        return "enum";
      case google::protobuf::FieldDescriptor::TYPE_SFIXED32:
        return "sfixed32";
      case google::protobuf::FieldDescriptor::TYPE_SFIXED64:
        return "sfixed64";
      case google::protobuf::FieldDescriptor::TYPE_SINT32:
        return "sint32";
      case google::protobuf::FieldDescriptor::TYPE_SINT64:
        return "sint64";
      default:
        return "unknown";
    };
  }

  public: void Write()
  {
    std::ofstream out("/tmp/p.html");
    out << "<html>\n";
    out << "<head>\n";
    out << "<link rel='stylesheet' href='https://fonts.googleapis.com/icon?family=Material+Icons'>";
    out << "<link rel='stylesheet' href='https://code.getmdl.io/1.3.0/material.indigo-pink.min.css'>";
    out << "<script defer src='https://code.getmdl.io/1.3.0/material.min.js'></script>";
    out << customCss;
    out << "</head>\n";

    out << "<body>\n";
    out << "<main class='mdl-layout__content'>\n";

    for (const std::pair<std::string,
         google::protobuf::DescriptorProto> &msg : this->messages)
    {
      out << "<h2>" << msg.second.name() << " in "
        << messagesLoc[msg.first] << "</h2>\n";

      out << "<h4>Fields</h4>";
      out << "<table class='mdl-data-table mdl-js-data-table mdl-shadow--2dp'>";
      out << "<thead><tr>"
          << "<th class='mdl-data-table__cell--non-numeric'>Name</th>"
          << "<th class='mdl-data-table__cell--non-numeric'>Type</th>"
          << "<th class='mdl-data-table__cell--non-numeric'>Label</th>"
          << "<th class='mdl-data-table__cell--non-numeric'>Description</th>"
          << "<th class='mdl-data-table__cell--non-numeric'>Number</th>"
          << "</tr></thead><tbody>";
      for (int fieldI = 0; fieldI < msg.second.field_size(); ++fieldI)
      {
        out << "<tr>";
        const google::protobuf::FieldDescriptorProto &field =
          msg.second.field(fieldI);
        out << "<td class='mdl-data-table__cell--non-numeric'>"
            << field.name() << "</td>"
            << "<td class='mdl-data-table__cell--non-numeric'>"
            << this->TypeName(field.type()) << "</td>";

        out << "<td class='mdl-data-table__cell--non-numeric'>";
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

        out << "<td class='mdl-data-table__cell--non-numeric'>"
          << this->messagesLoc[msg.first] << ".4." << fieldI << "</td>"
          << "<td class='mdl-data-table__cell--non-numeric'>"
          << field.number() << "</td>";
        out << "</tr>";
      }
      out << "</tbody></table>\n";
    }
    out << "</main>\n";

    out << "</body>\n";
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
  sourceTree.MapPath("", "/home/nkoenig/work/ignition/ign-msgs/test/proto");
  sourceTree.MapPath("ignition/msgs", "/home/nkoenig/work/ignition/ign-msgs/test/proto");

  ErrorCollector errorCollector;

  Doc doc;

  std::map<std::string, std::string> allComments;
  std::vector<std::string> protoFilenames;

  // For each proto file in the directory.
  for (common::DirIter dirIter(FLAGS_d);
       dirIter != common::DirIter(); ++dirIter)
  {
    // Make sure the file has the proto extension.
    if ((*dirIter).find(".proto") != (*dirIter).size() - 6)
      continue;

    // Setup the protobuf compiler importer.
    google::protobuf::compiler::Importer importer(&sourceTree,
        &errorCollector);

    // Get the base name of the protobuf file.
    std::string baseName = common::basename(*dirIter);
    protoFilenames.push_back(baseName);

    std::cout << "Basename[" << baseName << "]\n";

    // Get a file descriptor to the protobuf file.
    const google::protobuf::FileDescriptor *fileDescriptor =
      importer.Import(baseName);

    //
    google::protobuf::FileDescriptorProto fileDescriptorProto;
    fileDescriptor->CopySourceCodeInfoTo(&fileDescriptorProto);
    const google::protobuf::SourceCodeInfo &sci =
      fileDescriptorProto.source_code_info();

    std::cout << baseName << " Size[" << sci.location_size() << "]\n";
    for (int locI = 0; locI < sci.location_size(); ++locI)
    {
      const google::protobuf::SourceCodeInfo_Location &scil =
        sci.location(locI);

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
