
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/__init__.py DESTINATION ${GZ_PYTHON_INSTALL_PATH}/gz/${GZ_DESIGNATION})

if (BUILD_TESTING AND NOT WIN32)
  set(python_tests
    basic_TEST
  )
  execute_process(COMMAND "${Python3_EXECUTABLE}" -m pytest --version
    OUTPUT_VARIABLE PYTEST_output
    ERROR_VARIABLE  PYTEST_error
    RESULT_VARIABLE PYTEST_result)
  if(${PYTEST_result} EQUAL 0)
    set(pytest_FOUND TRUE)
  else()
    message(WARNING "Pytest package not available: ${PYTEST_error}")
    message(WARNING "Output: ${PYTEST_output}")
  endif()

  foreach (test ${python_tests})
    if (pytest_FOUND)
      add_test(NAME ${test}.py COMMAND
        "${Python3_EXECUTABLE}" -m pytest "${CMAKE_SOURCE_DIR}/python/test/${test}.py" --junitxml "${CMAKE_BINARY_DIR}/test_results/${test}.xml")
    else()
      add_test(NAME ${test}.py COMMAND
        "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/python/test/${test}.py")
    endif()
    set_tests_properties(${test}.py PROPERTIES
      ENVIRONMENT_MODIFICATION
        "PYTHONPATH=path_list_prepend:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python/;PYTHONPATH=path_list_prepend:${CMAKE_BINARY_DIR}/gz_msgs_gen/python;LD_LIBRARY_PATH=path_list_prepend:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR};LD_LIBRARY_PATH=path_list_prepend:${CMAKE_BINARY_DIR}/lib")
  endforeach()
endif()
