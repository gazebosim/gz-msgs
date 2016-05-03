include (${project_cmake_dir}/Utils.cmake)

set(ign_library_path "${CMAKE_BINARY_DIR}/src/cmd/cmdmsgs${PROJECT_MAJOR_VERSION}")

# Generate a configuration file for internal testing.
# Note that the major version of the library is included in the name.
# Ex: transport0.yaml
configure_file(
  "msgs.yaml.in"
    "${CMAKE_BINARY_DIR}/test/conf/msgs${PROJECT_MAJOR_VERSION}.yaml" @ONLY)

set(ign_library_path "${CMAKE_INSTALL_PREFIX}/lib/ruby/ignition/cmdmsgs${PROJECT_MAJOR_VERSION}")

# Generate a configuration file.
# Note that the major version of the library is included in the name.
# Ex: transport0.yaml
configure_file(
  "msgs.yaml.in"
    "${CMAKE_CURRENT_BINARY_DIR}/msgs${PROJECT_MAJOR_VERSION}.yaml" @ONLY)

# Install the yaml configuration files in an unversioned location.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/msgs${PROJECT_MAJOR_VERSION}.yaml
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/ignition/)
