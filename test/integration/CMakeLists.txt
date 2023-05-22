gz_get_sources(tests)

if(MSVC)
  # TODO: Check if/why this test doesn't work on Windows and find a fix.
  list(REMOVE_ITEM tests headers.cc)
endif()

gz_build_tests(TYPE INTEGRATION SOURCES ${tests} TEST_LIST test_targets)

foreach(test ${test_targets})
  target_include_directories(${test} PUBLIC ${PROJECT_BINARY_DIR}/gz_msgs_gen )
  target_link_libraries(${test} gz-msgs${PROJECT_VERSION_MAJOR}-compiled)
endforeach()
