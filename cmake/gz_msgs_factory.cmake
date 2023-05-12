##################################################
# A function that generates factory methods for generated gz-msgs
# The output of this is are a header and source file that can be used as part of your library
# for the gz::msgs::Factory
# Options:
# One value arguments:
#   FACTORY_GEN_SCRIPT  - Location of the factory generator script
#   PROTO_PACKAGE       - Protobuf package the file belongs to (e.g. "gz.msgs")
#   PROTOC_EXEC         - Path to protoc
#   OUTPUT_CPP_DIR      - Path where C++ files are saved
#   OUTPUT_CPP_HH_VAR   - A CMake variable name containing a list that the C++ headers should be appended to
#   OUTPUT_CPP_CC_VAR   - A Cmake variable name containing a list that the C++ sources should be appended to
# Multi value arguments
#   INPUT_PROTOS        - List of input proto files
#   PROTO_PATH          - Base directory of the proto files
function(gz_msgs_factory)
  set(options "")
  set(oneValueArgs
    FACTORY_GEN_SCRIPT
    PROTO_PACKAGE
    OUTPUT_CPP_DIR
    OUTPUT_CPP_HH_VAR
    OUTPUT_CPP_CC_VAR)
  set(multiValueArgs INPUT_PROTOS PROTO_PATH)

  cmake_parse_arguments(gz_msgs_factory "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(proto_package_dir ".")
  if(gz_msgs_factory_PROTO_PACKAGE)
    string(REPLACE "." "/" proto_package_dir ${gz_msgs_factory_PROTO_PACKAGE})
  endif()

  set(output_header "${gz_msgs_factory_OUTPUT_CPP_DIR}/${proto_package_dir}/MessageTypes.hh")
  set(output_source "${gz_msgs_factory_OUTPUT_CPP_DIR}/${proto_package_dir}/register.cc")

  list(APPEND ${gz_msgs_factory_OUTPUT_CPP_HH_VAR} ${output_header})
  list(APPEND ${gz_msgs_factory_OUTPUT_CPP_CC_VAR} ${output_source})

  list(APPEND output_files ${output_header})
  list(APPEND output_files ${output_source})

  set(${gz_msgs_factory_OUTPUT_CPP_HH_VAR} ${${gz_msgs_factory_OUTPUT_CPP_HH_VAR}} PARENT_SCOPE)
  set(${gz_msgs_factory_OUTPUT_CPP_CC_VAR} ${${gz_msgs_factory_OUTPUT_CPP_CC_VAR}} PARENT_SCOPE)

  set(depends_index)

  # Full path to an index file, which contains all defined message types for that proto file
  foreach(proto_file ${gz_msgs_factory_INPUT_PROTOS})
    get_filename_component(FIL_WE ${proto_file} NAME_WE)
    string(REPLACE "." "_" PACKAGE_UNDER ${gz_msgs_factory_PROTO_PACKAGE})
    string(REPLACE "." "_" MESSAGE_UNDER ${FIL_WE})
    set(input_index "${gz_msgs_factory_OUTPUT_CPP_DIR}/${PACKAGE_UNDER}_${MESSAGE_UNDER}.pb_index")
    list(APPEND depends_index ${input_index})
  endforeach()

  set(GENERATE_ARGS
    --output-cpp-path "${gz_msgs_factory_OUTPUT_CPP_DIR}"
    --proto-package "${gz_msgs_factory_PROTO_PACKAGE}"
    --proto-path "${gz_msgs_factory_PROTO_PATH}"
    --protos "${gz_msgs_factory_INPUT_PROTOS}"
    )

  add_custom_command(
    OUTPUT ${output_files}
    COMMAND Python3::Interpreter
    ARGS ${gz_msgs_factory_FACTORY_GEN_SCRIPT} ${GENERATE_ARGS}
    DEPENDS
      ${depends_index}
    # While the script is executed in the source directory, it does not write
    # to the source tree.  All outputs are stored in the build directory.
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Running factory generator"
    VERBATIM
  )

endfunction()
