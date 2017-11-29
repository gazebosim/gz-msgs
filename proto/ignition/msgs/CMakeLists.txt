file(GLOB proto_files "*.proto")

install(
  FILES ${proto_files}
  DESTINATION "${IGN_INCLUDE_INSTALL_DIR_FULL}/ignition/${IGN_DESIGNATION}"
  COMPONENT proto)
