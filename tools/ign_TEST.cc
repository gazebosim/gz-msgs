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

#include <string>
#include <gtest/gtest.h>
#include <ignition/msgs/config.hh>

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
  EXPECT_NE(std::string::npos, output.find("ign_msgs.WorldControl"));
}

/////////////////////////////////////////////////
TEST(CmdLine, MsgInfo)
{
  auto output = custom_exec_str("ign msg --info ign_msgs.WorldControl "
    "--force-version " + g_version);
  EXPECT_NE(std::string::npos, output.find("message WorldControl {"));
}
