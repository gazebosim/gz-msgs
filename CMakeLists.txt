cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(gz-msgs9 VERSION 9.4.0)

#============================================================================
# Find gz-cmake
#============================================================================
# If you get an error at this line, you need to install gz-cmake
find_package(gz-cmake3 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

gz_configure_project(VERSION_SUFFIX)

if (UNIX AND NOT APPLE)
  set (EXTRA_TEST_LIB_DEPS stdc++fs)
else()
  set (EXTRA_TEST_LIB_DEPS)
endif()

#============================================================================
# Set project-specific options
#============================================================================

# Cross-compilation related options
# In a cross-compilation scenario, it is possible that the gz_msgs_gen
# generator compiled for the target machine cannot be used to generate
# the C++ code corresponding to the .proto definition. For this scenario,
# the following two options can be used as follows.
# First of all, gz-msgs is compiled targeting the host machine, and in the
# build targeting the host, the INSTALL_GZ_MSGS_GEN_EXECUTABLE option is
# enabled:
# > cmake -DINSTALL_GZ_MSGS_GEN_EXECUTABLE:BOOL=ON ..
# ensuring that the gz_msgs_gen is installed in
# <host_install_prefix>/bin/gz_msgs_gen . Then, the same version of gz-msgs
# can be cross-compiled, and in the cross-compilation build the location of the
# host gz_msgs_gen is specified via the GZ_MSGS_GEN_EXECUTABLE
# CMake cache variable:
# > cmake -GZ_MSGS_GEN_EXECUTABLE=<host_install_prefix>/bin/gz_msgs_gen ..

# TODO(CH3): Deprecated. Remove IGN_MSGS CMake variables on tick-tock.
if(INSTALL_IGN_MSGS_GEN_EXECUTABLE)
  message(WARNING "INSTALL_IGN_MSGS_GEN_EXECUTABLE is deprecated, use INSTALL_GZ_MSGS_GEN_EXECUTABLE instead")
  set(INSTALL_GZ_MSGS_GEN_EXECUTABLE ${INSTALL_IGN_MSGS_GEN_EXECUTABLE})
else()
  option(
    INSTALL_GZ_MSGS_GEN_EXECUTABLE
    "Install the gz_msgs_gen executable."
    OFF)
  set(INSTALL_IGN_MSGS_GEN_EXECUTABLE ${INSTALL_GZ_MSGS_GEN_EXECUTABLE})
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
gz_find_package(GzProtobuf
                 VERSION ${REQ_PROTOBUF_VER}
                 REQUIRED
                 COMPONENTS all
                 PRETTY Protobuf)

#--------------------------------------
# Find gz-math
gz_find_package(gz-math7 REQUIRED)
set(GZ_MATH_VER ${gz-math7_VERSION_MAJOR})

#--------------------------------------
# Find if command is available. This is used to enable tests.
# Note that CLI files are installed regardless of whether the dependency is
# available during build time
find_program(HAVE_GZ_TOOLS gz)
set(GZ_TOOLS_VER 1)

#--------------------------------------
# Find Tinyxml2
gz_find_package(TINYXML2 REQUIRED PRIVATE PRETTY tinyxml2)

#============================================================================
# Configure the build
#============================================================================
gz_configure_build(QUIT_IF_BUILD_ERRORS)

#============================================================================
# gz command line support
#============================================================================
add_subdirectory(conf)

#============================================================================
# Test the command line commands
#============================================================================
add_subdirectory(tools)

#============================================================================
# Install proto files
#============================================================================
# TODO: Consider tweaking gz_configure_build() to call add_subdirectory(proto)
# whenever a proto subdirectory exists. This could be used alongside
# gz_msgs_protoc to get uniform support for proto messages across all Gazebo
# projects.
add_subdirectory(proto)

#============================================================================
# Create package information
#============================================================================
gz_create_packages()

#============================================================================
# Create documentation
#============================================================================
configure_file(${CMAKE_SOURCE_DIR}/api.md.in ${CMAKE_BINARY_DIR}/api.md)
configure_file(${CMAKE_SOURCE_DIR}/tutorials.md.in ${CMAKE_BINARY_DIR}/tutorials.md)


gz_create_docs(
  API_MAINPAGE_MD "${CMAKE_BINARY_DIR}/api.md"
  TUTORIALS_MAINPAGE_MD "${CMAKE_BINARY_DIR}/tutorials.md"
  AUTOGENERATED_DOC "${CMAKE_BINARY_DIR}/include/gz/msgs/details"
  TAGFILES
    "${GZ-MATH_DOXYGEN_TAGFILE} = ${GZ-MATH_API_URL}"
)

# Wait to build the doc for the autogenerated code
# The TARGET will exist if doxygen is installed
if(TARGET doc)
  add_dependencies(doc gz-msgs${PROJECT_VERSION_MAJOR})
endif()
