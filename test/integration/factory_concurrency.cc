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

#include <atomic>
#include <filesystem>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "gz/msgs/Factory.hh"
#include "gz/msgs/stringmsg.pb.h"

static constexpr const char * kMsgsTestPath = GZ_MSGS_TEST_PATH;

/////////////////////////////////////////////////
/// \brief Exercise every public Factory entry point from multiple threads
/// at once. MessageFactory documents that all member functions are thread
/// safe; under ThreadSanitizer this test also acts as a data race detector.
TEST(FactoryConcurrency, ParallelUse)
{
  const std::filesystem::path testPath(kMsgsTestPath);
  const std::string descPath = (testPath / "desc" / "stringmsg.desc").string();

  // Load the dynamic type up front so every creator thread can expect it.
  gz::msgs::Factory::LoadDescriptors(descPath);
  ASSERT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));

  // Static so that the lambdas below can read it without capturing it,
  // which MSVC requires even for constants (C3493).
  static constexpr int kIters = 10000;
  std::atomic<int> failures{0};
  std::vector<std::thread> threads;

  // Creators of a generated (registered) type.
  for (int t = 0; t < 4; ++t)
  {
    threads.emplace_back([&failures]
    {
      for (int i = 0; i < kIters; ++i)
      {
        if (!gz::msgs::Factory::New("gz.msgs.StringMsg"))
          ++failures;
      }
    });
  }

  // Creators of a type known only through descriptors.
  for (int t = 0; t < 2; ++t)
  {
    threads.emplace_back([&failures]
    {
      for (int i = 0; i < kIters / 10; ++i)
      {
        if (!gz::msgs::Factory::New("example.msgs.StringMsg"))
          ++failures;
      }
    });
  }

  // Registration of new types while the creators run.
  threads.emplace_back([]
  {
    for (int i = 0; i < kIters / 10; ++i)
    {
      gz::msgs::Factory::Register(
          "test.factory_concurrency.Msg" + std::to_string(i),
          [] { return std::make_unique<gz::msgs::StringMsg>(); });
    }
  });

  // Type enumeration while the maps are being read and written.
  threads.emplace_back([&failures]
  {
    for (int i = 0; i < kIters / 100; ++i)
    {
      std::vector<std::string> types;
      gz::msgs::Factory::Types(types);
      if (types.empty())
        ++failures;
    }
  });

  // Repeated descriptor loading of the same file.
  threads.emplace_back([&descPath]
  {
    for (int i = 0; i < 20; ++i)
    {
      gz::msgs::Factory::LoadDescriptors(descPath);
    }
  });

  for (auto &thread : threads)
    thread.join();

  EXPECT_EQ(0, failures);
  EXPECT_NE(nullptr, gz::msgs::Factory::New("gz.msgs.StringMsg"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("example.msgs.StringMsg"));
  EXPECT_NE(nullptr, gz::msgs::Factory::New("test.factory_concurrency.Msg0"));
}
