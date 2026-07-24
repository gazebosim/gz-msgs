/*
 * Copyright (C) 2026 Open Source Robotics Foundation
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

#include <gtest/gtest.h>

#include <filesystem>

#include <gz/utils/Environment.hh>

#include "gz/msgs/Factory.hh"

static constexpr const char * kMsgsTestPath = GZ_MSGS_TEST_PATH;

/////////////////////////////////////////////////
/// \brief The dynamic factory is constructed on first dynamic use, so
/// GZ_DESCRIPTOR_PATH is read at that point rather than at library load.
/// This test fails if descriptors are loaded eagerly at load time (the
/// environment variable is not set yet at that point) or if creating a
/// generated type wrongly triggers descriptor loading (it runs before the
/// variable is set below).
TEST(FactoryLazyTest, DescriptorPathReadAtFirstDynamicUse)
{
  // Creating a generated type must not construct the dynamic factory.
  EXPECT_NE(nullptr, gz::msgs::Factory::New("gz.msgs.StringMsg"));

  // Point GZ_DESCRIPTOR_PATH at the test descriptors only now, after the
  // process started and after a generated type was created.
  const std::filesystem::path testPath(kMsgsTestPath);
  ASSERT_TRUE(gz::utils::setenv(
      "GZ_DESCRIPTOR_PATH", (testPath / "desc").string()));

  // The first dynamic lookup reads the environment set above.
  EXPECT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
}
