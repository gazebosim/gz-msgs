set(TEST_TYPE "INTEGRATION")

set(tests
)

if (NOT MSVC)
  list(APPEND tests headers.cc)
endif()

ign_build_tests(TYPE INTEGRATION SOURCE ${tests})
