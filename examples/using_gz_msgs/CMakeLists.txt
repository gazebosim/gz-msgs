cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(using_gz_msgs VERSION 1.0.0)

#============================================================================
# Find gz-cmake
#============================================================================
find_package(gz-cmake3 REQUIRED)

find_package(gz-msgs10 REQUIRED)
set(GZ_MSGS_VER ${gz-msgs10_VERSION_MAJOR})

# Get the gz-msgs installed messages and generate a library from them
gz_msgs_get_installed_messages(
  MESSAGES_PATH_VARIABLE MSGS_PATH
  MESSAGES_PROTOS_VARIABLE MSGS_PROTOS)

gz_msgs_generate_messages(
  TARGET gz_msgs_gen
  PROTO_PACKAGE "gz.msgs"
  MSGS_PATH ${MSGS_PATH}
  MSGS_PROTOS ${MSGS_PROTOS})

add_executable(${PROJECT_NAME} main.cc)

# Automatically uses whole-archive linking to get all the messages available
target_link_messages(TARGET ${PROJECT_NAME} PUBLIC MSG_TARGETS gz_msgs_gen)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)
