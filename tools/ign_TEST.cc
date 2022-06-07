/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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

#include <filesystem>
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include <ignition/msgs/config.hh>
#include "ignition/msgs/test_config.h"

#ifdef _MSC_VER
#    define popen _popen
#    define pclose _pclose
#endif

static const std::string g_version(std::string(IGNITION_MSGS_VERSION_FULL));

/////////////////////////////////////////////////
std::string custom_exec_str(std::string _cmd)
{
  _cmd += " 2>&1";
  FILE *pipe = popen(_cmd.c_str(), "r");

  if (!pipe)
    return "ERROR";

  char buffer[128];
  std::string result = "";

  while (!feof(pipe))
  {
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }

  pclose(pipe);
  return result;
}

/////////////////////////////////////////////////
TEST(CmdLine, Versions)
{
  auto outputDebug = custom_exec_str("ign");
  auto output = custom_exec_str("ign msg --versions");
  EXPECT_NE(std::string::npos, output.find(g_version));
}

/////////////////////////////////////////////////
TEST(CmdLine, Help)
{
  auto output =
    custom_exec_str("ign msg --force-version " + g_version + " --help");
  EXPECT_NE(std::string::npos, output.find("list"));

  output = custom_exec_str("ign msg --force-version " + g_version + " -h");
  EXPECT_NE(std::string::npos, output.find("list"));

  output = custom_exec_str("ign msg --force-version " + g_version);
  EXPECT_NE(std::string::npos, output.find("list"));
}

/////////////////////////////////////////////////
TEST(CmdLine, MsgList)
{
  auto output = custom_exec_str("ign msg --list --force-version " +
    g_version);
  EXPECT_NE(std::string::npos, output.find("ign_msgs.WorldControl"))
    << output;
}

/////////////////////////////////////////////////
TEST(CmdLine, MsgInfo)
{
  auto output = custom_exec_str("ign msg --info ign_msgs.WorldControl "
    "--force-version " + g_version);
  EXPECT_NE(std::string::npos, output.find("message WorldControl {"))
    << output;
}

/////////////////////////////////////////////////
TEST(CmdLine, MsgHelpVsCompletionFlags)
{
  // Flags in help message
  auto helpOutput = custom_exec_str("ign msg --help --force-version "
    + g_version);

  // Call the output function in the bash completion script
  std::filesystem::path scriptPath = PROJECT_SOURCE_PATH;
  scriptPath = scriptPath / "src" / "cmd" / "msgs.bash_completion.sh";

  // Equivalent to:
  // sh -c "bash -c \". /path/to/msgs.bash_completion.sh; _gz_msgs_flags\""
  std::string cmd = "bash -c \". " + scriptPath.string() + "; _gz_msgs_flags\"";
  std::string scriptOutput = custom_exec_str(cmd);

  // Tokenize script output
  std::istringstream iss(scriptOutput);
  std::vector<std::string> flags((std::istream_iterator<std::string>(iss)),
    std::istream_iterator<std::string>());

  EXPECT_GT(flags.size(), 0u);

  // Match each flag in script output with help message
  for (std::string flag : flags)
  {
    EXPECT_NE(std::string::npos, helpOutput.find(flag)) << helpOutput;
  }
}

/////////////////////////////////////////////////
/// Main
int main(int argc, char **argv)
{
  // Set IGN_CONFIG_PATH to the directory where the .yaml configuration files
  // is located.
  setenv("IGN_CONFIG_PATH", IGN_CONFIG_PATH, 1);

  // Make sure that we load the library recently built and not the one installed
  // in your system.
  // Add the directory where ignition msgs has been built.
  std::string value = std::string(IGN_TEST_LIBRARY_PATH);
  // Save the current value of LD_LIBRARY_PATH.
  auto cvalue = std::getenv("LD_LIBRARY_PATH");
  if (cvalue)
    value += ":" + std::string(cvalue);
  setenv("LD_LIBRARY_PATH", value.c_str(), 1);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
