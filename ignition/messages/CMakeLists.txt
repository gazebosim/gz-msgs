set (msgs
clock.proto
cmd_vel2d.proto
color.proto
stringmsg.proto
stringmsg_v.proto
image.proto
images_stamped.proto
image_stamped.proto
int.proto
joint_cmd.proto
joint_wrench.proto
joint_wrench_stamped.proto
laserscan.proto
laserscan_stamped.proto
packet.proto
pid.proto
pointcloud.proto
pose.proto
poses_stamped.proto
pose_stamped.proto
pose_trajectory.proto
pose_v.proto
quaternion.proto
sonar.proto
sonar_stamped.proto
time.proto
vector2d.proto
vector3d.proto
web_request.proto
wrench.proto
wrench_stamped.proto
)

set(PROTO_SRCS)
set(PROTO_HDRS)

#file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/ignition/messages")
foreach(FIL ${msgs})
  get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
  get_filename_component(FIL_WE ${FIL} NAME_WE)

  list(APPEND PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/ignition/messages/${FIL_WE}.pb.cc")
  list(APPEND PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/ignition/messages/${FIL_WE}.pb.h")

  add_custom_command(
    OUTPUT
      "${CMAKE_CURRENT_BINARY_DIR}/ignition/messages/${FIL_WE}.pb.cc"
      "${CMAKE_CURRENT_BINARY_DIR}/ignition/messages/${FIL_WE}.pb.h"
    COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS --plugin=protoc-gen-ignmsgs=${CMAKE_BINARY_DIR}/src/ign_msgs_gen --cpp_out  ${CMAKE_CURRENT_BINARY_DIR}  --ignmsgs_out ${CMAKE_CURRENT_BINARY_DIR} --proto_path ${PROJECT_SOURCE_DIR} ${ABS_FIL}
    DEPENDS ${ABS_FIL} ign_msgs_gen
    COMMENT "Running C++ protocol buffer compiler on ${FIL}"
    VERBATIM )
endforeach()

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS}
  PROPERTIES GENERATED TRUE)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
ign_add_library(ignition_msgs
  ${PROTO_SRCS} ${PROJECT_SOURCE_DIR}/src/Factory.cc)
target_link_libraries(ignition_msgs ${PROTOBUF_LIBRARY})

add_dependencies(ignition_msgs ign_msgs_gen)

set (message_headers "" CACHE INTERNAL "Include dirs description")

foreach (hdr ${PROTO_HDRS})
  string (REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" hdr ${hdr})
  APPEND_TO_CACHED_STRING(message_headers
    "Message Types" "#include \"${hdr}\"\n")
endforeach()

ign_install_includes("" ${PROTO_HDRS})
ign_install_library(ignition_msgs)
ign_install_includes("" ${msgs})
