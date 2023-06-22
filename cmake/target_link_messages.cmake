# Copyright 2023 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

##################################################
# A function that does whole-archive linking for messages
# This is only required in the case that the static initialization based
# factory registration is needed. Whole archive linking guarantees that the
# messages are correctly registered with the factory.
# Alternatively, use the `RegisterAll` generated method to manually register.
# One value arguments:
#   TARGET              - Target to link MSGS_TARGETS messages into
# Multi value arguments
#   MSGS_TARGETS        - List of generated messages targets to link into TARGET
function(target_link_messages)
  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs MSG_TARGETS)

  cmake_parse_arguments(target_link_messages "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  foreach(message_lib ${target_link_messages_MSG_TARGETS})
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      # MSVC link flag doesn't work with generator expressions
      # TODO(mjcarroll) When CMake 3.24 is genrally available, use
      # linking generator expressions as described here:
      # https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:LINK_LIBRARY
      target_link_libraries(${target_link_messages_TARGET} -WHOLEARCHIVE:$<TARGET_FILE:${message_lib}>)

    else()
      target_link_libraries(${target_link_messages_TARGET}
          $<$<CXX_COMPILER_ID:GNU>:-Wl,--whole-archive>
          $<$<CXX_COMPILER_ID:Clang>:-force_load>
          $<$<CXX_COMPILER_ID:AppleClang>:-force_load> ${message_lib}
          $<$<CXX_COMPILER_ID:GNU>:-Wl,--no-whole-archive>)
    endif()

    # Explicitly add dependency, link libraries, and includes as the WHOLEARCHIVE flag doesn't
    # do that on Windows.
    add_dependencies(${target_link_messages_TARGET} ${message_lib})
    get_target_property(message_lib_INCLUDES ${message_lib} INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(message_lib_LIBS ${message_lib} INTERFACE_LINK_LIBRARIES)
    target_include_directories(${target_link_messages_TARGET} PRIVATE ${message_lib_INCLUDES})
    # Note: not using visibility here because it conflicts with gazebo-built tests that don't use
    # any visiblity parameter
    target_link_libraries(${target_link_messages_TARGET} ${message_lib_LIBS})
  endforeach()
endfunction()
