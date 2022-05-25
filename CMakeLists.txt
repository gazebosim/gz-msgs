cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(ignition-msgs9 VERSION 9.0.0)

#============================================================================
# Find ignition-cmake
#============================================================================
# If you get an error at this line, you need to install ignition-cmake
find_package(ignition-cmake3 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
ign_configure_project(
  REPLACE_IGNITION_INCLUDE_PATH gz/msgs
  VERSION_SUFFIX pre1)

#============================================================================
# Set project-specific options
#============================================================================

# Cross-compilation related options
# In a cross-compilation scenario, it is possible that the gz_msgs_gen
# generator compiled for the target machine cannot be used to generate
# the C++ code corresponding to the .proto definition. For this scenario,
# the following two options can be used as follows.
# First of all, ign-msgs is compiled targeting the host machine, and in the
# build targeting the host, the INSTALL_GZ_MSGS_GEN_EXECUTABLE option is
# enabled:
# > cmake -DINSTALL_GZ_MSGS_GEN_EXECUTABLE:BOOL=ON ..
# ensuring that the gz_msgs_gen is installed in
# <host_install_prefix>/bin/gz_msgs_gen . Then, the same version of ign-msgs
# can be cross-compiled, and in the cross-compilation build the location of the
# host gz_msgs_gen is specified via the GZ_MSGS_GEN_EXECUTABLE
# CMake cache variable:
# > cmake -GZ_MSGS_GEN_EXECUTABLE=<host_install_prefix>/bin/gz_msgs_gen ..

# TODO(CH3): Deprecated. Remove IGN_MSGS CMake variables on tick-tock.
if(INSTALL_IGN_MSGS_GEN_EXECUTABLE)
  message(WARNING "INSTALL_IGN_MSGS_GEN_EXECUTABLE is deprecated, use INSTALL_GZ_MSGS_GEN_EXECUTABLE instead")
  set(INSTALL_GZ_MSGS_GEN_EXECUTABLE INSTALL_IGN_MSGS_GEN_EXECUTABLE)
else()
  option(
    INSTALL_GZ_MSGS_GEN_EXECUTABLE
    "Install the gz_msgs_gen executable."
    OFF)
  set(INSTALL_IGN_MSGS_GEN_EXECUTABLE INSTALL_GZ_MSGS_GEN_EXECUTABLE)
endif()

mark_as_advanced(INSTALL_IGN_MSGS_GEN_EXECUTABLE)
mark_as_advanced(INSTALL_GZ_MSGS_GEN_EXECUTABLE)

set(
  GZ_MSGS_GEN_EXECUTABLE
  "$<TARGET_FILE:gz_msgs_gen>"
  CACHE STRING
  "gz_msgs_gen executable used in the gz_msgs_protoc CMake function.")
mark_as_advanced(GZ_MSGS_GEN_EXECUTABLE)

# TODO(CH3): Deprecated. Remove IGN_MSGS CMake variables on tick-tock.
set(
  IGN_MSGS_GEN_EXECUTABLE
  "$<TARGET_FILE:gz_msgs_gen>"
  CACHE STRING
  "gz_msgs_gen executable used in the gz_msgs_protoc CMake function.")
mark_as_advanced(IGN_MSGS_GEN_EXECUTABLE)

#============================================================================
# Search for project-specific dependencies
#============================================================================
message(STATUS "\n\n-- ====== Finding Dependencies ======")

#--------------------------------------
# Find Protobuf
set(REQ_PROTOBUF_VER 3)
ign_find_package(IgnProtobuf
                 VERSION ${REQ_PROTOBUF_VER}
                 REQUIRED
                 COMPONENTS all
                 PRETTY Protobuf)

#--------------------------------------
# Find ignition-math
ign_find_package(ignition-math7 REQUIRED)
set(IGN_MATH_VER ${ignition-math7_VERSION_MAJOR})

#--------------------------------------
# Find if ign command is available
find_program(HAVE_IGN_TOOLS ign)

#--------------------------------------
# Find Tinyxml2
ign_find_package(TINYXML2 REQUIRED PRIVATE PRETTY tinyxml2)

#============================================================================
# Configure the build
#============================================================================
ign_configure_build(QUIT_IF_BUILD_ERRORS)

#============================================================================
# ign command line support
#============================================================================
add_subdirectory(conf)

#============================================================================
# Test the command line commands
#============================================================================
add_subdirectory(tools)

#============================================================================
# Install proto files
#============================================================================
# TODO: Consider tweaking ign_configure_build() to call add_subdirectory(proto)
# whenever a proto subdirectory exists. This could be used alongside
# gz_msgs_protoc to get uniform support for proto messages across all ignition
# projects.
add_subdirectory(proto)

#============================================================================
# Create package information
#============================================================================
ign_create_packages()

#============================================================================
# Create documentation
#============================================================================
configure_file(${CMAKE_SOURCE_DIR}/api.md.in ${CMAKE_BINARY_DIR}/api.md)
configure_file(${CMAKE_SOURCE_DIR}/tutorials.md.in ${CMAKE_BINARY_DIR}/tutorials.md)


ign_create_docs(
  API_MAINPAGE_MD "${CMAKE_BINARY_DIR}/api.md"
  TUTORIALS_MAINPAGE_MD "${CMAKE_BINARY_DIR}/tutorials.md"
  AUTOGENERATED_DOC "${CMAKE_BINARY_DIR}/include/gz/msgs/"
  TAGFILES
    "${IGNITION-MATH_DOXYGEN_TAGFILE} = ${IGNITION-MATH_API_URL}"
)

# Wait to build the doc for the autogenerated code
# The TARGET will exist if doxygen is installed
if(TARGET doc)
  add_dependencies(doc ignition-msgs${PROJECT_VERSION_MAJOR})
endif()
