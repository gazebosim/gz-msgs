
ign_get_sources(tests)

if(MSVC)
  # TODO: Check if/why this test doesn't work on Windows and find a fix.
  list(REMOVE_ITEM tests headers.cc)
endif()

ign_build_tests(TYPE INTEGRATION SOURCES ${tests})
