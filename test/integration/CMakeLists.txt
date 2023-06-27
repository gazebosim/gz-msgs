gz_get_sources(tests)

if (NOT HAVE_GZ_TOOLS)
  list(REMOVE_ITEM tests gz_TEST.cc)
endif()

gz_build_tests(TYPE INTEGRATION SOURCES ${tests} TEST_LIST test_targets)

foreach(test ${test_targets})
  target_link_libraries(${test} ${PROJECT_LIBRARY_TARGET_NAME} gz_msgs_msgs)
endforeach()

if(TARGET INTEGRATION_gz_TEST)
  target_compile_definitions(INTEGRATION_gz_TEST PRIVATE
    "GZ_MSGS_EXECUTABLE_PATH=\"$<TARGET_FILE:gz-msgs>\""
    "GZ_MSGS_COMPLETION_SCRIPT_PATH=\"${PROJECT_SOURCE_DIR}/core/cmd/msgs.bash_completion.sh\"")
endif()

if(TARGET INTEGRATION_Factory_TEST)
  target_compile_definitions(INTEGRATION_Factory_TEST PRIVATE
    "GZ_MSGS_TEST_PATH=\"${PROJECT_SOURCE_DIR}/test\"")
endif()
