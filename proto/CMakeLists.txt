include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_string_utils.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_factory.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_generate.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_protoc.cmake)

set(proto_files
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/boolean.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/bytes.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/clock.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/empty.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/header.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/image.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/int32.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/int32_v.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/statistic.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/stringmsg.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/time.proto
  ${PROJECT_SOURCE_DIR}/proto/gz/msgs/vector3d.proto
  )

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
    gz-msgs${PROJECT_VERSION_MAJOR}
  TARGET
    gz-msgs${PROJECT_VERSION_MAJOR}-msgs
)

install(
  DIRECTORY gz
  DESTINATION ${GZ_DATA_INSTALL_DIR}/protos
  COMPONENT proto
  FILES_MATCHING PATTERN "*.proto")
