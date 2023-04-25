install(
  DIRECTORY gz
  DESTINATION share/protos
  COMPONENT proto
  FILES_MATCHING PATTERN "*.proto")
