set(python_init_file ${PROJECT_BINARY_DIR}/python/gz/${GS_DESIGNATION}/__init__.py)
configure_file(${PROJECT_SOURCE_DIR}/python/src/__init__.py.in ${python_init_file})

install(FILES ${python_init_file} DESTINATION ${CMAKE_INSTALL_PREFIX}/${GZ_LIB_INSTALL_DIR}/python/gz/${GZ_DESIGNATION}${PROJECT_VERSION_MAJOR})
