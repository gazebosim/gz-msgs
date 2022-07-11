##################################################
# Build a custom protoc plugin
gz_add_executable(gz_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(gz_msgs_gen
  protobuf::libprotoc
  protobuf::libprotobuf)
target_include_directories(gz_msgs_gen PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_compile_features(gz_msgs_gen PRIVATE ${GZ_CXX_11_FEATURES})

if (UNIX)
  target_link_libraries(gz_msgs_gen pthread)
endif()

if(INSTALL_GZ_MSGS_GEN_EXECUTABLE)
  set_target_properties(gz_msgs_gen PROPERTIES VERSION ${PROJECT_VERSION_FULL})
  install(TARGETS gz_msgs_gen DESTINATION ${GZ_BIN_INSTALL_DIR})

  # TODO(chapulina) Deprecated. Remove on v10.
  install(FILES $<TARGET_FILE:gz_msgs_gen> DESTINATION ${GZ_BIN_INSTALL_DIR} RENAME ign_msgs_gen PERMISSIONS OWNER_EXECUTE)
endif()

##################################################
# A function that calls protoc on a protobuf file
# Options:
#   GENERATE_RUBY       - generates ruby code for the message if specified
#   GENERATE_CPP        - generates c++ code for the message if specified
# One value arguments:
#   PROTO_PACKAGE       - Protobuf package the file belongs to (e.g. ".gz.msgs")
#   PROTOC_EXEC         - Path to protoc
#   INPUT_PROTO         - Path to the input .proto file
#   OUTPUT_CPP_DIR      - Path where C++ files are saved
#   OUTPUT_RUBY_DIR     - Path where Ruby files are saved
#   OUTPUT_CPP_HH_VAR   - A CMake variable name containing a list that the C++ header path should be appended to
#   OUTPUT_CPP_CC_VAR   - A Cmake variable name containing a list that the C++ source path should be appended to
#   OUTPUT_RUBY_VAR     - A Cmake variable name containing a list that the ruby file should be apenned to
# Multi value arguments
#   PROTO_PATH          - Passed to protoc --proto_path
function(gz_msgs_protoc)
  set(options GENERATE_RUBY GENERATE_CPP)
  set(oneValueArgs PROTO_PACKAGE PROTOC_EXEC INPUT_PROTO OUTPUT_CPP_DIR OUTPUT_RUBY_DIR OUTPUT_CPP_HH_VAR OUTPUT_CPP_CC_VAR OUTPUT_RUBY_VAR)
  set(multiValueArgs PROTO_PATH)

  cmake_parse_arguments(gz_msgs_protoc "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  get_filename_component(ABS_FIL ${gz_msgs_protoc_INPUT_PROTO} ABSOLUTE)
  get_filename_component(FIL_WE ${gz_msgs_protoc_INPUT_PROTO} NAME_WE)

  set(protoc_args)
  set(output_files)

  foreach(proto_path ${gz_msgs_protoc_PROTO_PATH})
    list(APPEND protoc_args "--proto_path=${proto_path}")
  endforeach()

  set(proto_package_dir ".")
  if(gz_msgs_protoc_PROTO_PACKAGE)
    string(REPLACE "." "/" proto_package_dir ${gz_msgs_protoc_PROTO_PACKAGE})
  endif()

  if(gz_msgs_protoc_GENERATE_CPP)
    set(output_header "${gz_msgs_protoc_OUTPUT_CPP_DIR}${proto_package_dir}/${FIL_WE}.pb.h")
    set(output_source "${gz_msgs_protoc_OUTPUT_CPP_DIR}${proto_package_dir}/${FIL_WE}.pb.cc")
    list(APPEND ${gz_msgs_protoc_OUTPUT_CPP_HH_VAR} ${output_header})
    list(APPEND ${gz_msgs_protoc_OUTPUT_CPP_CC_VAR} ${output_source})
    list(APPEND output_files ${output_header})
    list(APPEND output_files ${output_source})
    list(APPEND protoc_args "--plugin=protoc-gen-gzmsgs=${GZ_MSGS_GEN_EXECUTABLE}")
    list(APPEND protoc_args "--cpp_out=dllexport_decl=GZ_MSGS_VISIBLE:${gz_msgs_protoc_OUTPUT_CPP_DIR}")
    list(APPEND protoc_args "--gzmsgs_out" "${gz_msgs_protoc_OUTPUT_CPP_DIR}")
    set(${gz_msgs_protoc_OUTPUT_CPP_HH_VAR} ${${gz_msgs_protoc_OUTPUT_CPP_HH_VAR}} PARENT_SCOPE)
    set(${gz_msgs_protoc_OUTPUT_CPP_CC_VAR} ${${gz_msgs_protoc_OUTPUT_CPP_CC_VAR}} PARENT_SCOPE)
  endif()

  if(gz_msgs_protoc_GENERATE_RUBY)
    file(MAKE_DIRECTORY ${gz_msgs_protoc_OUTPUT_RUBY_DIR})
    set(output_ruby "${gz_msgs_protoc_OUTPUT_RUBY_DIR}${proto_package_dir}/${FIL_WE}_pb.rb")
    list(APPEND ${gz_msgs_protoc_OUTPUT_RUBY_VAR} ${output_ruby})
    list(APPEND output_files ${output_ruby})
    list(APPEND protoc_args "--ruby_out=${gz_msgs_protoc_OUTPUT_RUBY_DIR}")
    set(${gz_msgs_protoc_OUTPUT_RUBY_VAR} ${${gz_msgs_protoc_OUTPUT_RUBY_VAR}} PARENT_SCOPE)
  endif()

  #get_cmake_property(_variableNames VARIABLES)
  #foreach (_variableName ${_variableNames})
  #    message(STATUS "${_variableName}=${${_variableName}}")
  #endforeach()

  add_custom_command(
    OUTPUT
      ${output_files}
    COMMAND
      ${gz_msgs_protoc_PROTOC_EXEC}
    ARGS
      ${protoc_args}
      ${ABS_FIL}
    DEPENDS
      ${ABS_FIL}
      gz_msgs_gen
    COMMENT "Running protoc on ${gz_msgs_protoc_INPUT_PROTO}"
    VERBATIM)
endfunction()


##################################################
file (GLOB proto_files ${PROJECT_SOURCE_DIR}/proto/gz/msgs/*.proto)

foreach(proto_file ${proto_files})
  gz_msgs_protoc(
    PROTO_PACKAGE
      .gz.msgs
    GENERATE_CPP
    GENERATE_RUBY
    INPUT_PROTO
      ${proto_file}
    PROTOC_EXEC
      protobuf::protoc
    OUTPUT_CPP_DIR
      "${PROJECT_BINARY_DIR}/include"
    OUTPUT_RUBY_DIR
      "${PROJECT_BINARY_DIR}/ruby"
    OUTPUT_CPP_HH_VAR
      gen_headers
    OUTPUT_CPP_CC_VAR
      gen_sources
    OUTPUT_RUBY_VAR
      gen_ruby_scripts
    PROTO_PATH
      "${PROJECT_SOURCE_DIR}/proto")
endforeach()

if(NOT MSVC)
  # -Wno-switch-default flags is required for suppressing a warning in some of
  # the generated protobuf files.
  set_source_files_properties(${gen_sources} COMPILE_FLAGS -Wno-switch-default)
endif()

if(MSVC)
  # Warning #4251 is the "dll-interface" warning that tells you when types used
  # by a class are not being exported. These generated source files have private
  # members that don't get exported, so they trigger this warning. However, the
  # warning is not important since those members do not need to be interfaced
  # with.
  set_source_files_properties(${gen_sources} COMPILE_FLAGS "/wd4251 /wd4146")
  # Fix for protobuf 3.12 - allow big object files
  add_definitions(/bigobj)
endif()

set_source_files_properties(${gen_headers} ${gen_sources} ${gen_ruby_scripts}
  PROPERTIES GENERATED TRUE)

message(STATUS "Installing Ruby messages to ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/ruby/ignition/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}")
install(FILES ${gen_ruby_scripts} DESTINATION ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/ruby/ignition/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR})

message(STATUS "Installing Ruby messages to ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/ruby/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}")
install(FILES ${gen_ruby_scripts} DESTINATION ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/ruby/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR})

gz_install_includes(
  "${GZ_INCLUDE_INSTALL_DIR_POSTFIX}/gz/${GZ_DESIGNATION}"
  ${gen_headers})

##################################################
# Generate gz/msgs/MessageTypes.hh
foreach (hdr ${gen_headers})
  string(REPLACE "${PROJECT_BINARY_DIR}/include/" "" hdr ${hdr})
  string(CONCAT gz_msgs_headers ${gz_msgs_headers} "#include <${hdr}>\n")
endforeach()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/MessageTypes.hh.in
  ${PROJECT_BINARY_DIR}/include/gz/msgs/MessageTypes.hh)

gz_install_includes(
  "${GZ_INCLUDE_INSTALL_DIR_POSTFIX}/gz/${GZ_DESIGNATION}"
  "${PROJECT_BINARY_DIR}/include/gz/${GZ_DESIGNATION}/MessageTypes.hh")

##################################################
# Build the main library
gz_create_core_library(SOURCES
  ${gen_sources}
  ${PROJECT_SOURCE_DIR}/src/Factory.cc
  ${PROJECT_SOURCE_DIR}/src/Filesystem.cc
  ${PROJECT_SOURCE_DIR}/src/gz.cc
  ${PROJECT_SOURCE_DIR}/src/Utility.cc
)

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

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
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PRIVATE -Wno-extended-offsetof)
endif()

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR_FULL}>)

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

##################################################
# gz msgs command
if(NOT WIN32)
  add_subdirectory(cmd)
endif()
