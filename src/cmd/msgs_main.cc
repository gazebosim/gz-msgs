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

#include <gz/utils/cli/CLI.hpp>
#include <gz/utils/cli/GzFormatter.hpp>

#include "gz.hh"

//////////////////////////////////////////////////
/// \brief Enumeration of available commands
enum class MsgCommand
{
  kNone,
  kMsgInfo,
  kMsgList,
};

//////////////////////////////////////////////////
/// \brief Structure to hold all available message options
struct MsgOptions
{
  /// \brief Command to execute
  MsgCommand command{MsgCommand::kNone};

  int verboseLevel = 0;

  std::string msgName;
};

//////////////////////////////////////////////////
void runMsgCommand(const MsgOptions &_opt)
{
  switch(_opt.command)
  {
    case MsgCommand::kMsgInfo:
      cmdMsgInfo(_opt.msgName.c_str());
      break;
    case MsgCommand::kMsgList:
      cmdMsgList();
      break;
    case MsgCommand::kNone:
    default:
      // In the event that there is no command, display help
      throw CLI::CallForHelp();
      break;
  }
}

//////////////////////////////////////////////////
void addMsgFlags(CLI::App &_app)
{
  auto opt = std::make_shared<MsgOptions>();

  _app.add_flag_callback("-l,--list",
     [opt](){
       opt->command = MsgCommand::kMsgList;
     }, "List all message types.");

  _app.add_option_function<std::string>("-i,--info",
     [opt](const std::string &_msgName){
        opt->command = MsgCommand::kMsgInfo;
        opt->msgName = _msgName;
     }, "Get info about the specified message type.");


  _app.callback([opt](){
    runMsgCommand(*opt);
  });
}

//////////////////////////////////////////////////
int main(int argc, char** argv)
{
  CLI::App app{"Print information about Gazebo messages"};

  app.add_flag_callback("-v,--version", [](){
      std::cout << gzMsgsVersion() << std::endl;
      throw CLI::Success();
  });

  addMsgFlags(app);
  app.formatter(std::make_shared<GzFormatter>(&app));
  CLI11_PARSE(app, argc, argv);
}
