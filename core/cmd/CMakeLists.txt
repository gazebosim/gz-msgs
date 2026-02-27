# Define the desired output name of the executable
set(msgs_executable_output_name gz-msgs)
# Append "-exe" to cmake target name to differ from the library target name
set(msgs_executable gz-msgs-exe)
add_executable(${msgs_executable} msgs_main.cc)
set_target_properties(${msgs_executable}
  PROPERTIES OUTPUT_NAME ${msgs_executable_output_name})
target_link_libraries(${msgs_executable}
  ${PROJECT_LIBRARY_TARGET_NAME}
  gz-utils::cli
)

if(MSVC)
  # Suppress protobuf-related DLL interface warnings:
  # C4251: class needs dll-interface to be used by clients
  # C4275: non dll-interface class used as base for dll-interface class
  target_compile_options(${msgs_executable} PRIVATE /wd4251 /wd4275)
  # Add /LTCG to avoid linker restart when objects are compiled with /GL
  target_link_options(${msgs_executable} PRIVATE /LTCG)
endif()

set(EXE_INSTALL_DIR ${CMAKE_INSTALL_LIBEXECDIR}/gz/${GZ_DESIGNATION}/)
install(TARGETS ${msgs_executable} DESTINATION ${EXE_INSTALL_DIR})
set(executable_location "../../../${EXE_INSTALL_DIR}/$<TARGET_FILE_NAME:${msgs_executable}>")

set(cmd_script_generated "${CMAKE_CURRENT_BINARY_DIR}/cmd${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}.rb")
set(cmd_script_configured "${cmd_script_generated}.configured")

configure_file(
  "cmd${GZ_DESIGNATION}.rb.in"
  "${cmd_script_configured}"
  @ONLY)

file(GENERATE
  OUTPUT "${cmd_script_generated}"
  INPUT  "${cmd_script_configured}")

install(FILES ${cmd_script_generated} DESTINATION lib/ruby/gz)

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
    ${CMAKE_INSTALL_DATAROOTDIR}/gz/gz${GZ_TOOLS_VER}.completion.d)
