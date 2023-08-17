##################################################
# Build a custom protoc plugin
set(PROTOC_PLUGIN ${PROJECT_NAME}_protoc_plugin)

gz_add_executable(${PROTOC_PLUGIN}
  generator/Generator.cc
  generator/generator_main.cc)
target_link_libraries(${PROTOC_PLUGIN}
  protobuf::libprotoc
  protobuf::libprotobuf)
target_include_directories(${PROTOC_PLUGIN} PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_compile_features(${PROTOC_PLUGIN} PRIVATE ${GZ_CXX_11_FEATURES})

if (UNIX)
  target_link_libraries(${PROTOC_PLUGIN} pthread)
endif()

install(TARGETS ${PROTOC_PLUGIN} DESTINATION ${GZ_BIN_INSTALL_DIR})

##################################################
# Build core library
gz_get_libsources_and_unittests(sources gtest_sources)

add_library(${PROJECT_LIBRARY_TARGET_NAME}-core
  src/Factory.cc
  src/MessageFactory.cc
  src/DynamicFactory.cc
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIBRARY_TARGET_NAME}_get_install_prefix_impl.cc
)

target_include_directories(
  ${PROJECT_LIBRARY_TARGET_NAME}-core
  PUBLIC
    "$<INSTALL_INTERFACE:${GZ_INCLUDE_INSTALL_DIR_FULL}/>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/include>"
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/core/include>"
)

target_link_libraries(
  ${PROJECT_LIBRARY_TARGET_NAME}-core
  PUBLIC
    gz-utils${GZ_UTILS_VER}::gz-utils${GZ_UTILS_VER}
    protobuf::libprotobuf
)

gz_create_core_library(SOURCES
  src/gz.cc
)

include(GzRelocatableBinaries)
gz_add_get_install_prefix_impl(GET_INSTALL_PREFIX_FUNCTION gz::msgs::getInstallPrefix
                               GET_INSTALL_PREFIX_HEADER gz/msgs/InstallationDirectories.hh
                               OVERRIDE_INSTALL_PREFIX_ENV_VARIABLE GZ_MSGS_INSTALL_PREFIX)

install(
  TARGETS ${PROJECT_LIBRARY_TARGET_NAME}-core
  EXPORT ${PROJECT_LIBRARY_TARGET_NAME}
  LIBRARY DESTINATION ${GZ_LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${GZ_LIB_INSTALL_DIR}
  RUNTIME DESTINATION ${GZ_BIN_INSTALL_DIR}
  COMPONENT libraries)

target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    ${PROJECT_LIBRARY_TARGET_NAME}-core
    ${PROJECT_LIBRARY_TARGET_NAME}-msgs
    gz-math${GZ_MATH_VER}::gz-math${GZ_MATH_VER}
    TINYXML2::TINYXML2
)

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  SYSTEM PUBLIC $<TARGET_PROPERTY:protobuf::libprotobuf,INTERFACE_INCLUDE_DIRECTORIES>)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Disable warning in generated *.pb.cc code
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE -Wno-invalid-offsetof)
endif()

##################################################
# Build unit tests
# Build the unit tests.
gz_build_tests(TYPE UNIT
  SOURCES
    ${gtest_sources}
  LIB_DEPS
      TINYXML2::TINYXML2
)

add_subdirectory(include/gz/msgs)
add_subdirectory(src/cmd)
