include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/test
)

set (test_sources
  ign_TEST.cc
)

if (IGNITION-TOOLS_BINARY_DIRS)
  ign_build_tests(TYPE UNIT SOURCES ${test_sources})
  set_property(TEST UNIT_ign_TEST PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib")
endif ()
