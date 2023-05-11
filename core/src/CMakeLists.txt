##################################################
# Build the main library
gz_create_core_library(SOURCES
  Factory.cc
  MessageFactory.cc
  DynamicFactory.cc
)

target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    protobuf::libprotobuf
    gz-math${GZ_MATH_VER}::gz-math${GZ_MATH_VER}
  PRIVATE
    TINYXML2::TINYXML2
)

if (${Protobuf_VERSION} VERSION_LESS 3.12.0)
  # Older versions of protobuf (eg on focal) will throw up float-equal errors
  # Fixed via: https://github.com/protocolbuffers/protobuf/pull/6000
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE -Wno-float-equal)
endif()

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  SYSTEM PUBLIC $<TARGET_PROPERTY:protobuf::libprotobuf,INTERFACE_INCLUDE_DIRECTORIES>)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Disable warning in generated *.pb.cc code
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE -Wno-invalid-offsetof)
endif()

##################################################
# Build unit tests
gz_get_libsources_and_unittests(sources gtest_sources)

# Build the unit tests.
gz_build_tests(TYPE UNIT
  SOURCES
    ${gtest_sources}
  LIB_DEPS
      TINYXML2::TINYXML2
)
