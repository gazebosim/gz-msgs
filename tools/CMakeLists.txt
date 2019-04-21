include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/test
)
set (test_sources
  ign_TEST.cc
)

# Skip command line tests for Windows, see
# https://bitbucket.org/ignitionrobotics/ign-msgs/issues/28
if (MSVC)
  list(REMOVE_ITEM test_sources ign_TEST.cc)
endif()

if (IGNITION-TOOLS_BINARY_DIRS)
  ign_build_tests(TYPE UNIT SOURCES ${test_sources})
endif ()
