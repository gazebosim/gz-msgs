include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_string_utils.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_factory.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_generate.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gz_msgs_protoc.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/target_link_messages.cmake)

file (GLOB proto_files ${PROJECT_SOURCE_DIR}/proto/gz/msgs/*.proto)

foreach(proto_file ${proto_files})
  gz_msgs_protoc(
    MSGS_GEN_SCRIPT
      ${PROJECT_SOURCE_DIR}/tools/gz_msgs_generate.py
    PROTO_PACKAGE
      "gz.msgs"
    GENERATE_PYTHON
    INPUT_PROTO
      ${proto_file}
    PROTOC_EXEC
      protobuf::protoc
    OUTPUT_PYTHON_DIR
      "${PROJECT_BINARY_DIR}/python"
    OUTPUT_PYTHON_VAR
      gen_python_scripts
    PROTO_PATH
      "${PROJECT_SOURCE_DIR}/proto")
endforeach()

set_source_files_properties(
  ${gen_python_scripts}
  PROPERTIES GENERATED TRUE)

add_custom_target(gz_msgs_python ALL DEPENDS ${gen_python_scripts})

message(STATUS "Installing Python messages to ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/python/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}")
set(python_init_file ${PROJECT_BINARY_DIR}/python/gz/${GS_DESIGNATION}/__init__.py)
configure_file(${PROJECT_SOURCE_DIR}/python/src/__init__.py.in ${python_init_file})
list(APPEND gen_python_scripts "${python_init_file}")

install(FILES ${gen_python_scripts} DESTINATION ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/python/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR})
