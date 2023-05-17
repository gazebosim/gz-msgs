include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_factory.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_generate.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_protoc.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/target_link_messages.cmake)

file (GLOB proto_files ${PROJECT_SOURCE_DIR}/proto/gz/msgs/*.proto)

# Using the impl, rather than the extras function because we are building in-source
gz_msgs_generate_messages_impl(
  MSGS_GEN_SCRIPT
    ${PROJECT_SOURCE_DIR}/tools/gz_msgs_generate.py
  FACTORY_GEN_SCRIPT
    ${PROJECT_SOURCE_DIR}/tools/gz_msgs_generate_factory.py
  GZ_PROTOC_PLUGIN
    $<TARGET_FILE:${PROJECT_NAME}_protoc_plugin>
  INPUT_PROTOS
    ${proto_files}
  PROTO_PACKAGE
    "gz.msgs"
  PROTO_PATH
    ${PROJECT_SOURCE_DIR}/proto
  MSGS_LIB
    gz-msgs10
  TARGET
    gz_msgs_msgs
)

gz_add_component(compiled
  SOURCES gz.cc
  GET_TARGET_NAME compiled_target)

# Not using target_link_messages because  we are registering messages in gz.cc
target_link_libraries(${compiled_target} PRIVATE gz_msgs_msgs)

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

if (TARGET UNIT_Factory_TEST)
  target_compile_definitions(UNIT_Factory_TEST
    PRIVATE GZ_MSGS_TEST_PATH="${PROJECT_SOURCE_DIR}/test")
  target_link_messages(TARGET UNIT_Factory_TEST MSG_TARGETS gz_msgs_msgs)
endif()

if (TARGET UNIT_Utility_TEST)
  target_include_directories(UNIT_Utility_TEST PRIVATE ${PROJECT_BINARY_DIR}/gz_msgs_gen)
  target_link_messages(TARGET UNIT_Utility_TEST MSG_TARGETS gz_msgs_msgs)
endif()

if (TARGET UNIT_PointCloudPackedUtils_TEST)
  target_link_messages(TARGET UNIT_PointCloudPackedUtils_TEST MSG_TARGETS gz_msgs_msgs)
endif()
