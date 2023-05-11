include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_protoc.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_factory.cmake)

file (GLOB proto_files ${PROJECT_SOURCE_DIR}/proto/gz/msgs/*.proto)

foreach(proto_file ${proto_files})
    gz_msgs_protoc(
      MSGS_GEN_SCRIPT
        "${PROJECT_SOURCE_DIR}/tools/gz_msgs_generate.py"
      PROTO_PACKAGE
        "gz.msgs"
      GENERATE_CPP
      INPUT_PROTO
        ${proto_file}
      PROTOC_EXEC
        protobuf::protoc
      GZ_PROTOC_PLUGIN
        $<TARGET_FILE:gz_msgs_gen>
      OUTPUT_CPP_DIR
        "${PROJECT_BINARY_DIR}/gz_msgs_gen"
      OUTPUT_INCLUDES
        gen_includes
      OUTPUT_CPP_HH_VAR
        gen_headers
      OUTPUT_DETAIL_CPP_HH_VAR
        gen_detail_headers
      OUTPUT_CPP_CC_VAR
        gen_sources
      PROTO_PATH
        "${PROJECT_SOURCE_DIR}/proto")
endforeach()

gz_msgs_factory(
  FACTORY_GEN_SCRIPT
    "${PROJECT_SOURCE_DIR}/tools/gz_msgs_generate_factory.py"
  PROTO_PACKAGE
    "gz.msgs"
  INPUT_PROTOS
    ${proto_files}
  OUTPUT_CPP_DIR
    "${PROJECT_BINARY_DIR}/gz_msgs_gen"
  OUTPUT_CPP_HH_VAR
    gen_factory_headers
  OUTPUT_CPP_CC_VAR
    gen_factory_sources
  PROTO_PATH
    "${PROJECT_SOURCE_DIR}/proto")

set_source_files_properties(
  ${gen_headers}
  ${gen_detail_headers}
  ${gen_sources}
  ${gen_factory_headers}
  ${gen_factory_sources}
  PROPERTIES GENERATED TRUE)

if(WIN32)
  set_source_files_properties(${gen_sources}
    COMPILE_FLAGS "/wd4100 /wd4512 /wd4127 /wd4068 /wd4244 /wd4267 /wd4251 /wd4146")
endif()

gz_add_component(compiled
  SOURCES ${gen_sources} ${gen_factory_sources} gz.cc
  GET_TARGET_NAME compiled_target)

target_link_libraries(${compiled_target} PUBLIC protobuf::libprotobuf ${PROJECT_LIBRARY_TARGET_NAME})
target_include_directories(${compiled_target} PRIVATE ${PROJECT_BINARY_DIR}/gz_msgs_gen )
