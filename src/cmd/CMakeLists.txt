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
install(TARGETS ${msgs_executable} DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR}/)
