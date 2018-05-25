cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(ignition-msgs3 VERSION 3.0.0)

#============================================================================
# Find ignition-cmake
#============================================================================
# If you get an error at this line, you need to install ignition-cmake
find_package(ignition-cmake1 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
ign_configure_project(VERSION_SUFFIX pre2)

#============================================================================
# Set project-specific options
#============================================================================

# ignition-msgs currently has no options that are unique to it

#============================================================================
# Search for project-specific dependencies
#============================================================================
message(STATUS "\n\n-- ====== Finding Dependencies ======")

#--------------------------------------
# Find Protobuf
set(REQ_PROTOBUF_VER 3)
ign_find_package(IgnProtobuf
                 VERSION ${REQ_PROTOBUF_VER}
                 PKGCONFIG protobuf
                 PKGCONFIG_VER_COMPARISON >=
                 REQUIRED
                 PRETTY Protobuf)

#--------------------------------------
# Find ignition-math
ign_find_package(ignition-math5 REQUIRED)
set(IGN_MATH_VER ${ignition-math5_VERSION_MAJOR})

#--------------------------------------
# Find ignition-tools
ign_find_package(ignition-tools
                 QUIET)

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
# ign_msgs_protoc to get uniform support for proto messages across all ignition
# projects.
add_subdirectory(proto)

#============================================================================
# Create package information
#============================================================================
ign_create_packages()

#============================================================================
# Create documentation
#============================================================================
ign_create_docs(
  TAGFILES
    "${IGNITION-MATH_DOXYGEN_TAGFILE} = ${IGNITION-MATH_API_URL}"
  )
