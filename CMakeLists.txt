cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(gz-msgs10 VERSION 10.0.0)

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

gz_configure_project(VERSION_SUFFIX pre1
  CONFIG_EXTRAS "gz-msgs-extras.cmake.in")

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

option(
  INSTALL_GZ_MSGS_GEN_EXECUTABLE
  "Install the gz_msgs_gen executable."
  OFF)

mark_as_advanced(INSTALL_GZ_MSGS_GEN_EXECUTABLE)

set(
  GZ_MSGS_GEN_EXECUTABLE
  "$<TARGET_FILE:gz_msgs_gen>"
  CACHE STRING
  "gz_msgs_gen executable used in the gz_msgs_protoc CMake function.")
mark_as_advanced(GZ_MSGS_GEN_EXECUTABLE)

# Python interfaces vars
option(USE_SYSTEM_PATHS_FOR_PYTHON_INSTALLATION
      "Install python modules in standard system paths in the system"
      OFF)

option(USE_DIST_PACKAGES_FOR_PYTHON
      "Use dist-packages instead of site-package to install python modules"
      OFF)

#============================================================================
# Search for project-specific dependencies
#============================================================================
message(STATUS "\n\n-- ====== Finding Dependencies ======")

#--------------------------------------
# Find Protobuf
gz_find_package(GzProtobuf
                 REQUIRED
                 COMPONENTS all
                 PRETTY Protobuf)

#--------------------------------------
# Find gz-utils
gz_find_package(gz-utils2 REQUIRED)
set(GZ_UTILS_VER ${gz-utils2_VERSION_MAJOR})

#--------------------------------------
# Find gz-math
gz_find_package(gz-math7 REQUIRED)
set(GZ_MATH_VER ${gz-math7_VERSION_MAJOR})

find_package(Python3 REQUIRED COMPONENTS Interpreter)

#--------------------------------------
# Find if command is available. This is used to enable tests.
# Note that CLI files are installed regardless of whether the dependency is
# available during build time
find_program(HAVE_GZ_TOOLS gz)
set(GZ_TOOLS_VER 1)

#--------------------------------------
# Find Tinyxml2
gz_find_package(TINYXML2 REQUIRED PRIVATE PRETTY tinyxml2)

#--------------------------------------
# Find DL if doing relocatable installation
if (GZ_ENABLE_RELOCATABLE_INSTALL)
  gz_find_package(DL REQUIRED)
endif()

#--------------------------------------
# Find Python
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
add_subdirectory(proto)

# Generate python
add_subdirectory(python)

#============================================================================
# Create package information
#============================================================================
gz_create_packages()

#============================================================================
# Install cmake extras for downstream users
#============================================================================
# Necessary to populate generator expressions
file(
  GENERATE
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gz-cmake/gz-msgs-extras.cmake"
  INPUT "${CMAKE_CURRENT_BINARY_DIR}/gz-cmake/gz-msgs-extras.cmake"
)

# Install cmake support files
install(
  DIRECTORY cmake/
  DESTINATION "${PROJECT_CMAKE_EXTRAS_INSTALL_DIR}"
)

#============================================================================
# Create documentation
#============================================================================
configure_file(${CMAKE_SOURCE_DIR}/api.md.in ${CMAKE_BINARY_DIR}/api.md)
configure_file(${CMAKE_SOURCE_DIR}/tutorials.md.in ${CMAKE_BINARY_DIR}/tutorials.md)


gz_create_docs(
  API_MAINPAGE_MD "${CMAKE_BINARY_DIR}/api.md"
  TUTORIALS_MAINPAGE_MD "${CMAKE_BINARY_DIR}/tutorials.md"
  TAGFILES
    "${GZ-MATH_DOXYGEN_TAGFILE} = ${GZ-MATH_API_URL}"
)

# Wait to build the doc for the autogenerated code
# The TARGET will exist if doxygen is installed
if(TARGET doc)
  add_dependencies(doc gz-msgs${PROJECT_VERSION_MAJOR})
endif()
