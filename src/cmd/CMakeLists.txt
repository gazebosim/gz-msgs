# Make a small static lib of command line functions
add_library(gz STATIC gz.cc)
target_link_libraries(gz
  ${PROJECT_LIBRARY_TARGET_NAME}
)

# Build msgs CLI executable
set(msgs_executable gz-msgs)
add_executable(${msgs_executable} msgs_main.cc)
target_link_libraries(${msgs_executable}
  gz
  gz-utils${GZ_UTILS_VER}::cli
  ${PROJECT_LIBRARY_TARGET_NAME}
)

set(EXE_INSTALL_DIR ${CMAKE_INSTALL_LIBEXECDIR}/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}/)
install(TARGETS ${msgs_executable} DESTINATION ${EXE_INSTALL_DIR})

#===============================================================================
# Used for the installed version.
# Generate the ruby script that gets installed.
# Note that the major version of the library is included in the name.
# Ex: cmdplugin2.rb
set(cmd_script_generated "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/cmd${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}.rb")
set(cmd_script_configured "${CMAKE_CURRENT_BINARY_DIR}/cmd${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}.rb.configured")

# Set the library_location variable to the relative path to the library file
# within the install directory structure.
set(executable_location "../../../${EXE_INSTALL_DIR}/$<TARGET_FILE_NAME:${msgs_executable}>")

configure_file(
  "cmd${GZ_DESIGNATION}.rb.in"
  "${cmd_script_configured}"
  @ONLY)

file(GENERATE
  OUTPUT "${cmd_script_generated}"
  INPUT  "${cmd_script_configured}")

# Install the ruby command line library in an unversioned location.
install(FILES ${cmd_script_generated} DESTINATION lib/ruby/gz)

gz_build_tests(
  TYPE UNIT
  SOURCES gz_TEST.cc
  LIB_DEPS
    gz
  TEST_LIST test_targets)

foreach(test ${test_targets})
  target_compile_definitions(${test} PRIVATE
    "GZ_MSGS_EXECUTABLE_PATH=\"$<TARGET_FILE:${msgs_executable}>\""
    "GZ_MSGS_VERSION_FULL=\"${PROJECT_VERSION}\""
    "GZ_MSGS_COMPLETION_SCRIPT_PATH=\"${PROJECT_SOURCE_DIR}/src/cmd/msgs.bash_completion.sh\"")
  endforeach()
