include (${project_cmake_dir}/Utils.cmake)
include (CheckCXXSourceCompiles)

include (${project_cmake_dir}/FindOS.cmake)
include (FindPkgConfig)

execute_process(COMMAND pkg-config --modversion protobuf
  OUTPUT_VARIABLE PROTOBUF_VERSION
  RESULT_VARIABLE protobuf_modversion_failed)

########################################
if (PROTOBUF_VERSION LESS 2.3.0)
  BUILD_ERROR("Incorrect version: Ignition Messages requires protobuf "
              "version 2.3.0 or greater")
endif()

########################################
# The Google Protobuf library for message generation + serialization
find_package(Protobuf REQUIRED)
if (NOT PROTOBUF_FOUND)
  BUILD_ERROR ("Missing: Google Protobuf (libprotobuf-dev)")
endif()
if (NOT PROTOBUF_PROTOC_EXECUTABLE)
  BUILD_ERROR ("Missing: Google Protobuf Compiler (protobuf-compiler)")
endif()
if (NOT PROTOBUF_PROTOC_LIBRARY)
  BUILD_ERROR ("Missing: Google Protobuf Compiler Library (libprotoc-dev)")
endif()

########################################
# The protobuf ruby bindings.
find_program(RUBY_PROTOBUF protoc-gen-ruby)
set(RUBY_INSTALL_DIR lib/ruby)
if (NOT RUBY_PROTOBUF_FOUND)
  BUILD_WARNING ("Missing: protobuf ruby bindings (sudo gem install protobuf)")
endif()

########################################
# Include man pages stuff
include (${project_cmake_dir}/Ronn2Man.cmake)
add_manpage_target()

#################################################
# Macro to check for visibility capability in compiler
# Original idea from: https://gitorious.org/ferric-cmake-stuff/ 
macro (check_gcc_visibility)
  include (CheckCXXCompilerFlag)
  check_cxx_compiler_flag(-fvisibility=hidden GCC_SUPPORTS_VISIBILITY)
endmacro()

########################################
# Find ignition math in unix platforms
# In Windows we expect a call from configure.bat script with the paths
find_package(ignition-math3 REQUIRED QUIET)
if (NOT ignition-math3_FOUND)
  message(STATUS "Looking for ignition-math3-config.cmake - not found")
  BUILD_ERROR ("Missing: Ignition math3 library.")
else()
  message(STATUS "Looking for ignition-math3-config.cmake - found")
endif()

#################################################
# Find ign command line utility:
find_package(ignition-tools)
if (IGNITION-TOOLS_BINARY_DIRS)
  set (HAVE_IGN TRUE)
else()
  BUILD_WARNING ("ignition-tools not found, for command line utilities, please install ignition-tools.")
endif()
