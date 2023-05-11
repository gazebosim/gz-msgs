##################################################
# Build a custom protoc plugin
gz_add_executable(gz_msgs_gen Generator.cc generator_main.cc)
target_link_libraries(gz_msgs_gen
  protobuf::libprotoc
  protobuf::libprotobuf)
target_include_directories(gz_msgs_gen PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_compile_features(gz_msgs_gen PRIVATE ${GZ_CXX_11_FEATURES})

if (UNIX)
  target_link_libraries(gz_msgs_gen pthread)
endif()

if(INSTALL_GZ_MSGS_GEN_EXECUTABLE)
  set_target_properties(gz_msgs_gen PROPERTIES VERSION ${PROJECT_VERSION_FULL})
  install(TARGETS gz_msgs_gen DESTINATION ${GZ_BIN_INSTALL_DIR})

  # TODO(chapulina) Deprecated. Remove on v10.
  install(FILES $<TARGET_FILE:gz_msgs_gen> DESTINATION ${GZ_BIN_INSTALL_DIR} RENAME ign_msgs_gen PERMISSIONS OWNER_EXECUTE)
endif()
