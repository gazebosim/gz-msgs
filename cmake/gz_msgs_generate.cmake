##################################################
# The implementation of gz_msgs_generate_messages
# Options:
# One value arguments:
#   MSGS_GEN_SCRIPT     - Location of the messge generator script
#   FACTORY_GEN_SCRIPT  - Location of the factory generator script
#   GZ_PROTOC_PLUGIN    - Location of the gazebo generator plugin
#   PROTO_PATH          - Base directory of the proto files
#   PROTO_PACKAGE       - Protobuf package the file belongs to (e.g. "gz.msgs")
#   MSGS_LIB            - gz-msgs library to link to
#   TARGET              - Target (static library) to create
# Multi value arguments
#   INPUT_PROTOS        - List of input proto files
#   DEPENDENCIES        - List of generated messages targets that these messages depend on
#                         Primarily used when generating new custom messages downstream
#                         that depend on gz-msgs
function(gz_msgs_generate_messages_impl)
  set(options "")
  set(oneValueArgs TARGET PROTO_PACKAGE MSGS_GEN_SCRIPT GZ_PROTOC_PLUGIN FACTORY_GEN_SCRIPT MSGS_LIB PROTO_PATH)
  set(multiValueArgs INPUT_PROTOS DEPENDENCIES)

  cmake_parse_arguments(generate_messages "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _gz_msgs_proto_pkg_to_string(${generate_messages_PROTO_PACKAGE} gen_dir)

  # Extract dependency information from targets
  set(depends_proto_paths)
  set(depends_includes)

  foreach(dep ${generate_messages_DEPENDENCIES})
    get_target_property(dep_proto_path ${dep} PROTO_DIR)
    get_target_property(dep_proto_include_path ${dep} PROTO_INCLUDE_DIR)

    list(APPEND depends_proto_paths ${dep_proto_path})
    list(APPEND depends_includes ${dep_proto_include_path})
  endforeach()

  foreach(proto_file ${generate_messages_INPUT_PROTOS})
    gz_msgs_protoc(
      MSGS_GEN_SCRIPT
        ${generate_messages_MSGS_GEN_SCRIPT}
      PROTO_PACKAGE
        ${generate_messages_PROTO_PACKAGE}
      GENERATE_CPP
      INPUT_PROTO
        ${proto_file}
      PROTOC_EXEC
        protobuf::protoc
      GZ_PROTOC_PLUGIN
        ${generate_messages_GZ_PROTOC_PLUGIN}
      OUTPUT_CPP_DIR
        "${PROJECT_BINARY_DIR}/${gen_dir}_gen"
      OUTPUT_INCLUDES
        gen_includes
      OUTPUT_CPP_HH_VAR
        gen_headers
      OUTPUT_DETAIL_CPP_HH_VAR
        gen_detail_headers
      OUTPUT_CPP_CC_VAR
        gen_sources
      PROTO_PATH
        ${generate_messages_PROTO_PATH}
      DEPENDENCY_PROTO_PATHS
        ${depends_proto_paths}
    )
  endforeach()

  gz_msgs_factory(
    FACTORY_GEN_SCRIPT
      ${generate_messages_FACTORY_GEN_SCRIPT}
    PROTO_PACKAGE
      ${generate_messages_PROTO_PACKAGE}
    INPUT_PROTOS
      ${generate_messages_INPUT_PROTOS}
    OUTPUT_CPP_DIR
      "${PROJECT_BINARY_DIR}/${gen_dir}_gen"
    OUTPUT_CPP_HH_VAR
      gen_factory_headers
    OUTPUT_CPP_CC_VAR
      gen_factory_sources
    PROTO_PATH
      ${generate_messages_PROTO_PATH}
  )

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

  if(NOT MSVC)
    # -Wno-switch-default flags is required for suppressing a warning in some of
    # the generated protobuf files.
    set_source_files_properties(${gen_sources} COMPILE_FLAGS "-Wno-switch-default -Wno-float-equal")
  endif()

  add_library(${generate_messages_TARGET} STATIC ${gen_sources} ${gen_factory_sources})

  # Use position indepedent code (-fPIC), because this library may be linked
  # into a shared library by the consumer
  set_property(TARGET ${generate_messages_TARGET} PROPERTY POSITION_INDEPENDENT_CODE ON)

  # Export the messages path and dependency messages paths for potential dependent message libs
  set(PROTO_DIR)
  list(APPEND PROTO_DIR ${generate_messages_PROTO_PATH})
  list(APPEND PROTO_DIR ${depends_proto_paths})

  set(PROTO_INCLUDE_DIR)
  list(APPEND PROTO_INCLUDE_DIR ${PROJECT_BINARY_DIR}/${gen_dir}_gen)
  list(APPEND PROTO_INCLUDE_DIR ${depends_includes})

  set_target_properties(${generate_messages_TARGET} PROPERTIES PROTO_DIR "${PROTO_DIR}")
  set_target_properties(${generate_messages_TARGET} PROPERTIES PROTO_INCLUDE_DIR "${PROTO_INCLUDE_DIR}")

  foreach(dep ${generate_messages_DEPENDENCIES})
    add_dependencies(${generate_messages_TARGET} ${dep})
  endforeach()

  target_link_libraries(${generate_messages_TARGET} PUBLIC protobuf::libprotobuf ${generate_messages_MSGS_LIB})
  target_include_directories(${generate_messages_TARGET} PUBLIC ${PROJECT_BINARY_DIR}/${gen_dir}_gen ${depends_includes})
endfunction()
