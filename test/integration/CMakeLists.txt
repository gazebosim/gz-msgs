gz_get_sources(tests)

list(REMOVE_ITEM tests Utility_TEST.cc PointCloudPackedUtils_TEST.cc Factory_TEST.cc headers.cc)

gz_build_tests(TYPE INTEGRATION SOURCES ${tests} TEST_LIST test_targets)

foreach(test ${test_targets})
  target_link_libraries(${test} gz-msgs${PROJECT_VERSION_MAJOR}-msgs)
endforeach()
