# Set the library name.
if (APPLE)
  set(IGN_LIB_BASENAME lib${PROJECT_NAME_LOWER}.dylib)
else()
  set(IGN_LIB_BASENAME lib${PROJECT_NAME_LOWER}.so)
endif()

# Used only for internal testing.
set(IGN_LIBRARY_NAME ../../../../lib/${IGN_LIB_BASENAME})

# Generate the ruby script for internal testing.
# Note that the major version of the library is included in the name.
# Ex: cmdmsgs0.rb
configure_file(
  "cmdmsgs.rb.in"
    "${CMAKE_BINARY_DIR}/test/lib/ruby/ignition/cmdmsgs${PROJECT_VERSION_MAJOR}.rb" @ONLY)

# Used for the installed version.
#
# Specify the library path relative to the location of the .rb script.
# E.g.: cmdmsgs0.rb is installed in:
#   /home/caguero/local/lib/ruby/ignition/cmdmsgs0.rb
# The Ignition Msgs library is installed in:
#   /home/caguero/local/lib/libignition-msgs0.so
# The value of IGN_LIBRARY_NAME should be:
#   ../../libignition-msgs0.so
set(IGN_LIBRARY_NAME ../../../${CMAKE_INSTALL_LIBDIR}/${IGN_LIB_BASENAME})

# Generate the ruby script that is installed.
# Note that the major version of the library is included in the name.
# Ex: cmdmsgs0.rb
configure_file(
  "cmdmsgs.rb.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmdmsgs${PROJECT_VERSION_MAJOR}.rb" @ONLY)

# Install the ruby command line library in an unversioned location.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmdmsgs${PROJECT_VERSION_MAJOR}.rb DESTINATION lib/ruby/ignition)
