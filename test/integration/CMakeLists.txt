gz_get_sources(tests)

if(MSVC)
  # TODO: Check if/why this test doesn't work on Windows and find a fix.
  list(REMOVE_ITEM tests headers.cc)
endif()

gz_build_tests(TYPE INTEGRATION SOURCES ${tests})

if (TARGET INTEGRATION_descriptors)
  target_compile_definitions(INTEGRATION_descriptors
    PRIVATE GZ_MSGS_TEST_PATH="${PROJECT_SOURCE_DIR}/test")
endif()
