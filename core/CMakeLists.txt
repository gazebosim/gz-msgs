# Build a custom protoc plugin
##################################################
gz_add_executable(${PROJECT_NAME}_protoc_plugin
  ${CMAKE_CURRENT_SOURCE_DIR}/generator/Generator.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/generator/generator_main.cc)
target_link_libraries(${PROJECT_NAME}_protoc_plugin
  protobuf::libprotoc
  protobuf::libprotobuf)
target_include_directories(${PROJECT_NAME}_protoc_plugin PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_compile_features(${PROJECT_NAME}_protoc_plugin PRIVATE ${GZ_CXX_11_FEATURES})

if (UNIX)
  target_link_libraries(${PROJECT_NAME}_protoc_plugin pthread)
endif()

install(
  TARGETS ${PROJECT_NAME}_protoc_plugin
  DESTINATION ${GZ_BIN_INSTALL_DIR})


gz_get_libsources_and_unittests(sources tests)

# Create the library target
gz_create_core_library(
  SOURCES ${sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DynamicFactory.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MessageFactory.cc
)

target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
  protobuf::libprotobuf
  gz-utils${GZ_UTILS_VER}::gz-utils${GZ_UTILS_VER}
)

# Build the unit tests
#gz_build_tests(
#  TYPE UNIT
#  SOURCES ${tests})

add_subdirectory(include/gz/msgs)
