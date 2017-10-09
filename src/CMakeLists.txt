# Turn on C++11 support for the library.
set(CMAKE_CXX_STANDARD 11)

# Collect source files into the "sources" variable and unit test files into the
# "gtest_sources" variable.
ign_get_libsources_and_unittests(sources gtest_sources)

set (sources
)

#set (gtest_sources
#  Factory_TEST.cc
#  Utility_TEST.cc
#)

include_directories (${PROTOBUF_INCLUDE_DIR}
                     ${IGNITION-MATH_INCLUDE_DIRS})
ign_add_executable(ign_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(ign_msgs_gen
  ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY})
target_compile_features(ign_msgs_gen PRIVATE cxx_variadic_macros)

if (UNIX)
  target_link_libraries(ign_msgs_gen pthread)
endif()

# Build the unit tests.
ign_build_tests(TYPE UNIT SOURCES ${gtest_sources})

add_subdirectory(cmd)
