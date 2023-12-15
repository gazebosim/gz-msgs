set(msgs_executable gz-msgs)
add_executable(${msgs_executable} msgs_main.cc)
target_link_libraries(${msgs_executable}
  ${PROJECT_LIBRARY_TARGET_NAME}
  gz-utils${GZ_UTILS_VER}::cli
)

set(EXE_INSTALL_DIR ${CMAKE_INSTALL_LIBEXECDIR}/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}/)
install(TARGETS ${msgs_executable} DESTINATION ${EXE_INSTALL_DIR})
set(executable_location "../../../${EXE_INSTALL_DIR}/$<TARGET_FILE_NAME:${msgs_executable}>")

configure_file(
  "cmd${GZ_DESIGNATION}.rb.in"
  "${cmd_script_configured}"
  @ONLY)

file(GENERATE
  OUTPUT "${cmd_script_generated}"
  INPUT  "${cmd_script_configured}")

install(FILES ${cmd_script_generated} DESTINATION lib/ruby/gz)
