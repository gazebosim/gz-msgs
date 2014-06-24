include (${project_cmake_dir}/Utils.cmake)

set (sources
)

set (gtest_sources
)

add_executable(ign_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(ign_msgs_gen ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY} pthread)

# ign_build_tests(${gtest_sources})
# ign_add_library(${PROJECT_NAME_LOWER} ${sources})
# ign_install_library(${PROJECT_NAME_LOWER})
