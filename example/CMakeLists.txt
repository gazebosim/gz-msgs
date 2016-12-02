cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Find the Ignition_Transport library
find_package(ignition-msgs0 QUIET REQUIRED)
include_directories(${IGNITION-MSGS_INCLUDE_DIRS})
link_directories(${IGNITION-MSGS_LIBRARY_DIRS})

# Generate examples
if (EXISTS "${CMAKE_SOURCE_DIR}/a_test.cc")
  add_executable(a_test a_test.cc)
  target_link_libraries(a_test ${IGNITION-MSGS_LIBRARIES})
endif()

if (MSVC)
  # Suppress Protobuf message generation warnings.
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4018 /wd4100 /wd4127 /wd4244 /wd4267 /wd4512")

  # Suppress the "decorated name length exceed" warning (inside the STL).
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4503")

  set(BUILD_SHARED_LIBS FALSE)
  add_definitions(-DBUILDING_STATIC_LIBS -DWIN32_LEAN_AND_MEAN)

  # Don't pull in the Windows min/max macros
  add_definitions(-DNOMINMAX)

  # Copy the Ignition Messages DLL.
  add_custom_command(TARGET a_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${IGNITION-MSGS_FOLDER}/lib/ignition-msgs0.dll"
    $<TARGET_FILE_DIR:a_test> VERBATIM)

endif()
