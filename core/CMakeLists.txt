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

gz_create_core_library(SOURCES
  src/Factory.cc
  src/MessageFactory.cc
  src/DynamicFactory.cc
)

target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    protobuf::libprotobuf
    gz-math${GZ_MATH_VER}::gz-math${GZ_MATH_VER}
  PRIVATE
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
