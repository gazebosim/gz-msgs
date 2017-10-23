set(TEST_TYPE "INTEGRATION")

set(tests
)

if (NOT MSVC)
  list(APPEND tests headers.cc)
endif()

link_directories(${PROJECT_BINARY_DIR}/test)

ign_build_tests(${tests})
