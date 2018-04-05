cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(ignition-msgs1 VERSION 1.0.0)

#============================================================================
# Find ignition-cmake
#============================================================================
# If you get an error at this line, you need to install ignition-cmake
find_package(ignition-cmake0 0.3.0 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
ign_configure_project()

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
if(MSVC)
  # On Windows we require version 3+ in order to have proper support for
  # shared libraries.
  set(REQ_PROTOBUF_VER 3)
  set(PROTOBUF_PURPOSE "Windows requires version 3+ to ensure proper support for DLLs")
else()
  set(REQ_PROTOBUF_VER 2.3.0)
  set(PROTOBUF_PURPOSE)
endif()
ign_find_package(IgnProtobuf
                 VERSION ${REQ_PROTOBUF_VER}
                 PKGCONFIG protobuf
                 PKGCONFIG_VER_COMPARISON >=
                 REQUIRED
                 PRETTY Protobuf
                 PURPOSE ${PROTOBUF_PURPOSE})

#--------------------------------------
# Find ignition-math
ign_find_package(ignition-math4 REQUIRED)

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
