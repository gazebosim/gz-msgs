##################################################
# Build a custom protoc plugin
ign_add_executable(ign_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(ign_msgs_gen
  ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY})
target_include_directories(ign_msgs_gen PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_compile_features(ign_msgs_gen PRIVATE ${IGN_CXX_11_FEATURES})

if (UNIX)
  target_link_libraries(ign_msgs_gen pthread)
endif()


##################################################
# A function that calls protoc on a protobuf file
# Options:
#   GENERATE_RUBY       - generates ruby code for the message if specified
#   GENERATE_CPP        - generates c++ code for the message if specified
# One value arguments:
#   PROTO_PACKAGE       - Protobuf package the file belongs to (e.g. ".ignition.msgs")
#   PROTOC_EXEC         - Path to protoc
#   INPUT_PROTO         - Path to the input .proto file
#   OUTPUT_CPP_DIR      - Path where C++ files are saved
#   OUTPUT_RUBY_DIR     - Path where Ruby files are saved
#   OUTPUT_CPP_HH_VAR   - A CMake variable name containing a list that the C++ header path should be appended to
#   OUTPUT_CPP_CC_VAR   - A Cmake variable name containing a list that the C++ source path should be appended to
#   OUTPUT_RUBY_VAR     - A Cmake variable name containing a list that the ruby file should be apenned to
# Multi value arguments
#   PROTO_PATH          - Passed to protoc --proto_path
function(ign_msgs_protoc)
  set(options GENERATE_RUBY GENERATE_CPP)
  set(oneValueArgs PROTO_PACKAGE PROTOC_EXEC INPUT_PROTO OUTPUT_CPP_DIR OUTPUT_RUBY_DIR OUTPUT_CPP_HH_VAR OUTPUT_CPP_CC_VAR OUTPUT_RUBY_VAR)
  set(multiValueArgs PROTO_PATH)

  cmake_parse_arguments(ign_msgs_protoc "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  get_filename_component(ABS_FIL ${ign_msgs_protoc_INPUT_PROTO} ABSOLUTE)
  get_filename_component(FIL_WE ${ign_msgs_protoc_INPUT_PROTO} NAME_WE)

  set(protoc_args)
  set(output_files)

  foreach(proto_path ${ign_msgs_protoc_PROTO_PATH})
    list(APPEND protoc_args "--proto_path=${proto_path}")
  endforeach()

  set(proto_package_dir ".")
  if(ign_msgs_protoc_PROTO_PACKAGE)
    string(REPLACE "." "/" proto_package_dir ${ign_msgs_protoc_PROTO_PACKAGE})
  endif()

  if(ign_msgs_protoc_GENERATE_CPP)
    set(output_header "${ign_msgs_protoc_OUTPUT_CPP_DIR}${proto_package_dir}/${FIL_WE}.pb.h")
    set(output_source "${ign_msgs_protoc_OUTPUT_CPP_DIR}${proto_package_dir}/${FIL_WE}.pb.cc")
    list(APPEND ${ign_msgs_protoc_OUTPUT_CPP_HH_VAR} ${output_header})
    list(APPEND ${ign_msgs_protoc_OUTPUT_CPP_CC_VAR} ${output_source})
    list(APPEND output_files ${output_header})
    list(APPEND output_files ${output_source})
    list(APPEND protoc_args "--plugin=protoc-gen-ignmsgs=$<TARGET_FILE:ign_msgs_gen>")
    list(APPEND protoc_args "--cpp_out=dllexport_decl=IGNITION_MSGS_VISIBLE:${ign_msgs_protoc_OUTPUT_CPP_DIR}")
    list(APPEND protoc_args "--ignmsgs_out" "${ign_msgs_protoc_OUTPUT_CPP_DIR}")
    set(${ign_msgs_protoc_OUTPUT_CPP_HH_VAR} ${${ign_msgs_protoc_OUTPUT_CPP_HH_VAR}} PARENT_SCOPE)
    set(${ign_msgs_protoc_OUTPUT_CPP_CC_VAR} ${${ign_msgs_protoc_OUTPUT_CPP_CC_VAR}} PARENT_SCOPE)
  endif()

  if(ign_msgs_protoc_GENERATE_RUBY)
    set(output_ruby "${ign_msgs_protoc_OUTPUT_RUBY_DIR}${proto_package_dir}/${FIL_WE}.pb.rb")
    list(APPEND ${ign_msgs_protoc_OUTPUT_RUBY_VAR} ${output_ruby})
    list(APPEND output_files ${output_ruby})
    list(APPEND protoc_args "--ruby_out=${ign_msgs_protoc_OUTPUT_RUBY_DIR}")
    set(${ign_msgs_protoc_OUTPUT_RUBY_VAR} ${${ign_msgs_protoc_OUTPUT_RUBY_VAR}} PARENT_SCOPE)
  endif()

  #get_cmake_property(_variableNames VARIABLES)
  #foreach (_variableName ${_variableNames})
  #    message(STATUS "${_variableName}=${${_variableName}}")
  #endforeach()

  add_custom_command(
    OUTPUT
      ${output_files}
    COMMAND
      ${ign_msgs_protoc_PROTOC_EXEC}
    ARGS
      ${protoc_args}
      ${ABS_FIL}
    DEPENDS
      ${ABS_FIL}
      ign_msgs_gen
    COMMENT "Running protoc on ${ign_msgs_protoc_INPUT_PROTO}"
    VERBATIM)
endfunction()


##################################################
# do the code generation
set(proto_headers)
set(proto_sources)
set(proto_ruby_scripts)

file (GLOB proto_files ${PROJECT_SOURCE_DIR}/ignition/msgs/*.proto)

set(gen_ruby GENERATE_RUBY)
if(WIN32 OR NOT RUBY_PROTOBUF_FOUND)
  set(gen_ruby)
endif()

foreach(proto_file ${proto_files})
  ign_msgs_protoc(
    PROTO_PACKAGE
      .ignition.msgs
    GENERATE_CPP
    ${gen_ruby}
    INPUT_PROTO
      ${proto_file}
    PROTOC_EXEC
      ${PROTOBUF_PROTOC_EXECUTABLE}
    OUTPUT_CPP_DIR
      "${PROJECT_BINARY_DIR}/include"
    OUTPUT_RUBY_DIR
      "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_CPP_HH_VAR
      gen_headers
    OUTPUT_CPP_CC_VAR
      gen_sources
    OUTPUT_RUBY_VAR
      gen_ruby_scripts
    PROTO_PATH
      "${PROJECT_SOURCE_DIR}")
endforeach()

# -Wno-switch-default flags is required for suppressing a warning in some of
# the generated protobuf files.
set_source_files_properties(${gen_headers} ${gen_sources} ${gen_ruby_scripts}
  PROPERTIES GENERATED TRUE COMPILE_FLAGS -Wno-switch-default)

message(STATUS "Installing Ruby messages to ${RUBY_INSTALL_DIR}/ignition/${IGN_DESIGNATION}")
install(FILES ${proto_ruby_scripts} DESTINATION ${RUBY_INSTALL_DIR}/ignition/${IGN_DESIGNATION})

ign_install_includes(
  "${IGN_INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_DESIGNATION}"
  ${gen_headers})


##################################################
# Generate ignition/msgs/MessageTypes.hh
foreach (hdr ${gen_headers})
  string(REPLACE "${PROJECT_BINARY_DIR}/include/" "" hdr ${hdr})
  string(CONCAT ign_msgs_headers ${ign_msgs_headers} "#include <${hdr}>\n")
endforeach()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/MessageTypes.hh.in
  ${PROJECT_BINARY_DIR}/include/ignition/msgs/MessageTypes.hh)

ign_install_includes(
  "${IGN_INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_DESIGNATION}"
  "${PROJECT_BINARY_DIR}/include/ignition/${IGN_DESIGNATION}/MessageTypes.hh")


##################################################
# Build the main library
ign_add_library(${PROJECT_LIBRARY_TARGET_NAME}
  ${gen_sources}
  ${PROJECT_SOURCE_DIR}/src/Factory.cc
  ${PROJECT_SOURCE_DIR}/src/ign.cc
  ${PROJECT_SOURCE_DIR}/src/Utility.cc)

target_compile_features(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE ${IGN_CXX_11_FEATURES})

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    ${PROTOBUF_LIBRARY}
    ${ignition-math4_LIBRARIES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Disable warning in generated *.pb.cc code
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE -Wno-extended-offsetof)
endif()

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR_FULL}>
    $<BUILD_INTERFACE:${PROTOBUF_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${PROTOBUF_INCLUDE_DIR}>)

ign_install_library()


##################################################
# Build unit tests
ign_get_libsources_and_unittests(sources gtest_sources)

# Build the unit tests.
ign_build_tests(TYPE UNIT
  SOURCES
    ${gtest_sources})

##################################################
# ign msgs command
add_subdirectory(cmd)
