include (${project_cmake_dir}/Utils.cmake)

set (headers
  Factory.hh
  Generator.hh
  System.hh
  Utility.hh
  ign.hh
)

set (ign_headers "" CACHE INTERNAL "Ignition headers" FORCE)
foreach (hdr ${headers})
  APPEND_TO_CACHED_STRING(ign_headers
    "Ignition headers" "#include <ignition/${IGN_PROJECT_NAME}/${hdr}>\n")
endforeach()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/ign_auto_headers.hh.in
  ${CMAKE_CURRENT_BINARY_DIR}/msgs.hh)

ign_install_includes("${INCLUDE_INSTALL_DIR_POSTFIX}/ignition"
  ${CMAKE_CURRENT_BINARY_DIR}/msgs.hh)

ign_install_includes(
  "${INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_PROJECT_NAME}" ${headers})
