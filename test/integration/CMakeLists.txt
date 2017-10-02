set(TEST_TYPE "INTEGRATION")

set(tests
  headers.cc
)

ign_build_tests(TYPE INTEGRATION SOURCE ${tests})
