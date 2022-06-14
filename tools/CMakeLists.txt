include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/test
)
set (test_sources
  ign_TEST.cc
)

# Skip command line tests for Windows, see
# https://github.com/ignitionrobotics/ign-msgs/issues/28
if (MSVC)
  list(REMOVE_ITEM test_sources ign_TEST.cc)
endif()

if (HAVE_IGN_TOOLS)
  ign_build_tests(
    TYPE UNIT
    SOURCES ${test_sources}
    LIB_DEPS
      ${EXTRA_TEST_LIB_DEPS})
endif ()
