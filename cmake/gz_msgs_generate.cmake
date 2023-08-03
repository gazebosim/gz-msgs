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
  _gz_msgs_proto_pkg_to_path(${generate_messages_PROTO_PACKAGE} proto_package_dir)

  # Extract dependency information from targets
  set(depends_proto_paths)
  set(depends_includes)

  set(target_name ${PROJECT_NAME}-${generate_messages_TARGET})

  set(output_directory ${PROJECT_BINARY_DIR}/${target_name}_genmsg)
  file(MAKE_DIRECTORY ${output_directory})

  foreach(dep ${generate_messages_DEPENDENCIES})
    get_target_property(msgs_desc_file ${dep} GZ_MSGS_DESC_FILE)

    message(STATUS ${dep} "--" ${msgs_desc_file})

    list(APPEND depends_msgs_desc ${msgs_desc_file})
  endforeach()

  foreach(proto_file ${generate_messages_INPUT_PROTOS})
    gz_msgs_protoc(
      MSGS_GEN_SCRIPT
        ${generate_messages_MSGS_GEN_SCRIPT}
      PROTO_PACKAGE
        ${generate_messages_PROTO_PACKAGE}
      INPUT_PROTO
        ${proto_file}
      PROTOC_EXEC
        protobuf::protoc
      GZ_PROTOC_PLUGIN
        ${generate_messages_GZ_PROTOC_PLUGIN}
      PROTO_PATH
        ${generate_messages_PROTO_PATH}
      DEPENDENCY_PROTO_DESCS
        ${depends_msgs_desc}

      # Cpp Specific arguments
      GENERATE_CPP
      OUTPUT_INCLUDES
        gen_includes
      OUTPUT_CPP_HH_VAR
        gen_headers
      OUTPUT_DETAIL_CPP_HH_VAR
        gen_detail_headers
      OUTPUT_CPP_CC_VAR
        gen_sources
      OUTPUT_CPP_DIR
        ${output_directory}

      # Python Specific arguments
      GENERATE_PYTHON
      OUTPUT_PYTHON_VAR
        gen_sources_py
      OUTPUT_PYTHON_DIR
        ${output_directory}/python/
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
      ${output_directory}
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

  set(ARGS)
  list(APPEND ARGS -I${generate_messages_PROTO_PATH})
  list(APPEND ARGS --descriptor_set_out="${target_name}.gz_desc")

  foreach(dep ${generate_messages_DEPENDENCIES})
    list(APPEND ARGS --descriptor_set_in="${msgs_desc_file}")
  endforeach()

  list(APPEND ARGS ${generate_messages_INPUT_PROTOS})

  add_custom_command(
    OUTPUT "${target_name}.gz_desc"
    COMMAND protobuf::protoc
    ARGS ${ARGS}
    DEPENDS ${generate_messages_INPUT_PROTOS}
    WORKING_DIRECTORY ${output_directory}
    COMMENT "Generating descriptor set"
  )

  add_library(${target_name} SHARED ${gen_sources} ${gen_factory_sources} ${target_name}.gz_desc)

  foreach(dep ${generate_messages_DEPENDENCIES})
    add_dependencies(${target_name} ${dep})
  endforeach()

  target_link_libraries(${target_name} PUBLIC protobuf::libprotobuf ${generate_messages_MSGS_LIB} ${generate_messages_DEPENDENCIES})
  target_include_directories(${target_name} PUBLIC
    "$<INSTALL_INTERFACE:${GZ_INCLUDE_INSTALL_DIR_FULL}/>"
    "$<BUILD_INTERFACE:${output_directory}>")

  set_target_properties(
    ${target_name}
      PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_FULL}
        GZ_MSGS_DESC_FILE "\$\{_IMPORT_PREFIX\}/share/gz/protos/${generate_messages_TARGET}.gz_desc"
        )
  set_property(TARGET ${target_name} PROPERTY EXPORT_PROPERTIES "GZ_MSGS_DESC_FILE")

  install(
    TARGETS ${target_name}
    EXPORT ${target_name}
    LIBRARY DESTINATION ${GZ_LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${GZ_LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${GZ_BIN_INSTALL_DIR}
    COMPONENT libraries)

  install(FILES ${gen_headers} ${gen_factory_headers} DESTINATION ${GZ_INCLUDE_INSTALL_DIR_FULL}/${proto_package_dir})
  install(FILES ${gen_detail_headers} DESTINATION ${GZ_INCLUDE_INSTALL_DIR_FULL}/${proto_package_dir}/details)
  install(FILES ${output_directory}/${target_name}.gz_desc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/gz/protos/)

  if (NOT GZ_PYTHON_INSTALL_PATH)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    if(USE_SYSTEM_PATHS_FOR_PYTHON_INSTALLATION)
      if(USE_DIST_PACKAGES_FOR_PYTHON)
        string(REPLACE "site-packages" "dist-packages" GZ_PYTHON_INSTALL_PATH ${Python3_SITELIB})
      else()
        # Python3_SITELIB might use dist-packages in some platforms
        string(REPLACE "dist-packages" "site-packages" GZ_PYTHON_INSTALL_PATH ${Python3_SITELIB})
      endif()
    else()
      # If not a system installation, respect local paths
      set(GZ_PYTHON_INSTALL_PATH ${GZ_LIB_INSTALL_DIR}/python)
    endif()
  endif()
  install(FILES ${gen_sources_py} DESTINATION ${GZ_PYTHON_INSTALL_PATH}/gz/msgs${GZ_MSGS_VER})

  set(component_name ${generate_messages_TARGET})
  set(component_pkg_name ${target_name})
  _gz_create_cmake_package(COMPONENT ${component_name})
  _gz_create_pkgconfig(COMPONENT ${component_name})
endfunction()
