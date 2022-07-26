include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/test
)
set (test_sources
  gz_TEST.cc
)

# Skip command line tests for Windows, see
# https://github.com/gazebosim/gz-msgs/issues/28
if (MSVC)
  list(REMOVE_ITEM test_sources gz_TEST.cc)
endif()

if (HAVE_GZ_TOOLS)
  gz_build_tests(
    TYPE UNIT
    SOURCES ${test_sources}
    LIB_DEPS
      ${EXTRA_TEST_LIB_DEPS})
endif ()
