cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#============================================================================
# Find ignition-cmake
#============================================================================
# If you get an error at this line, you need to install ignition-cmake
find_package(ignition-cmake0 REQUIRED)

#============================================================================
# Set up the project
#============================================================================
ign_configure_project(msgs 1.0.0)

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
ign_find_package(Protobuf
                 VERSION 2.3.0
                 PKGCONFIG_VER_COMPARISON >=
                 REQUIRED)

#--------------------------------------
# Find ignition-msgs
set(IGN_MATH_VER 3)
ign_find_package(ignition-math${IGN_MATH_VER}
                 REQUIRED)

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
# Generate all messages
#============================================================================
add_subdirectory(ignition/msgs)

#============================================================================
# Create package information
#============================================================================
ign_create_packages()
