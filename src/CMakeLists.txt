include (${project_cmake_dir}/Utils.cmake)

set (sources
)

set (gtest_sources
  Factory_TEST.cc
  Utility_TEST.cc
)

include_directories (${PROTOBUF_INCLUDE_DIR}
                     ${IGNITION-MATH_INCLUDE_DIRS})
add_executable(ign_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(ign_msgs_gen
  ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY})

if (UNIX)
  target_link_libraries(ign_msgs_gen pthread)
endif()

# When the minimum CMake required version will be >= 3.1 
# we could use the target_compile_features() command 
# to enable C++11 support in a platform-independent way. 
if(NOT MSVC)
  target_compile_options(ign_msgs_gen PUBLIC "-std=c++11")
endif()

link_directories(${IGNITION-MATH_LIBRARY_DIRS}) 
ign_build_tests(${gtest_sources})
add_subdirectory(cmd)
