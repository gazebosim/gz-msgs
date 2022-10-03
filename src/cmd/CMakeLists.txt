#===============================================================================
# Generate the ruby script for internal testing.
ign_generate_cmd()

#===============================================================================
# Bash completion

# Tack version onto and install the bash completion script
configure_file(
  "msgs.bash_completion.sh"
    "${CMAKE_CURRENT_BINARY_DIR}/msgs${PROJECT_VERSION_MAJOR}.bash_completion.sh" @ONLY)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/msgs${PROJECT_VERSION_MAJOR}.bash_completion.sh
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/gz/gz${IGN_TOOLS_VER}.completion.d)
