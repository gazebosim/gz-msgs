ign_install_all_headers(
  GENERATED_HEADERS
    MessageTypes.hh
  EXCLUDE_FILES
    SuppressWarning.hh
)

install(
  FILES
    SuppressWarning.h
  DESTINATION ${IGN_INCLUDE_INSTALL_DIR_FULL}/${PROJECT_INCLUDE_DIR}
)
