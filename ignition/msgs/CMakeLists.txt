include_directories(${PROTOBUF_INCLUDE_DIRS})

set (msgs
altimeter.proto
any.proto
atmosphere.proto
axis.proto
battery.proto
boolean.proto
boxgeom.proto
bytes.proto
camera_cmd.proto
camera_lens.proto
camerasensor.proto
cessna.proto
clock.proto
cmd_vel2d.proto
collision.proto
color.proto
contact.proto
contactsensor.proto
contacts.proto
cylindergeom.proto
density.proto
diagnostics.proto
distortion.proto
double.proto
double_v.proto
duration.proto
empty.proto
entity_factory.proto
float.proto
float_v.proto
fluid.proto
fog.proto
friction.proto
geometry.proto
gps.proto
gps_sensor.proto
gui_camera.proto
gui.proto
header.proto
heightmapgeom.proto
hydra.proto
imagegeom.proto
image.proto
images_stamped.proto
image_stamped.proto
imu.proto
imu_sensor.proto
inertial.proto
int32.proto
int32_v.proto
int64.proto
int64_v.proto
joint_animation.proto
joint_cmd.proto
joint.proto
joint_wrench.proto
joint_wrench_stamped.proto
joystick.proto
laserscan.proto
laserscan_stamped.proto
light.proto
link_data.proto
link.proto
log_control.proto
logical_camera_image.proto
logical_camera_sensor.proto
log_playback_control.proto
log_playback_stats.proto
log_status.proto
magnetometer.proto
marker.proto
marker_v.proto
material.proto
meshgeom.proto
model_configuration.proto
model.proto
model_v.proto
packet.proto
param.proto
param_v.proto
physics.proto
pid.proto
planegeom.proto
plugin.proto
plugin_v.proto
pointcloud.proto
polylinegeom.proto
pose_animation.proto
pose.proto
poses_stamped.proto
pose_stamped.proto
pose_trajectory.proto
pose_v.proto
projector.proto
propagation_grid.proto
propagation_particle.proto
publishers.proto
publish.proto
quaternion.proto
raysensor.proto
request.proto
response.proto
rest_login.proto
rest_logout.proto
rest_post.proto
rest_response.proto
road.proto
scene.proto
selection.proto
sensor_noise.proto
sensor.proto
sensor_v.proto
server_control.proto
shadows.proto
sim_event.proto
sky.proto
sonar.proto
sonar_stamped.proto
spheregeom.proto
spherical_coordinates.proto
stringmsg.proto
stringmsg_v.proto
subscribe.proto
surface.proto
tactile.proto
test.proto
time.proto
topic_info.proto
track_visual.proto
uint32.proto
uint32_v.proto
uint64.proto
uint64_v.proto
undo_redo.proto
user_cmd.proto
user_cmd_stats.proto
vector2d.proto
vector3d.proto
visual.proto
visual_v.proto
web_request.proto
wind.proto
wireless_node.proto
wireless_nodes.proto
world_control.proto
world_modify.proto
world_reset.proto
world_stats.proto
wrench.proto
wrench_stamped.proto
)

set(PROTO_SRCS)
set(PROTO_HDRS)
set(PROTO_RB)


foreach(FIL ${msgs})
  get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
  get_filename_component(FIL_WE ${FIL} NAME_WE)

  list(APPEND PROTO_SRCS
    "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.cc")
  list(APPEND PROTO_HDRS
    "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.h")

  # Add Ruby generation when we start using protobuf 3, which
  # should have a built in ruby generator
  if (WIN32 OR NOT RUBY_PROTOBUF_FOUND)
    add_custom_command(
      OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.h"
      COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --plugin=protoc-gen-ignmsgs=$<TARGET_FILE:ign_msgs_gen>
           --cpp_out=dllexport_decl=IGNITION_MSGS_VISIBLE:${CMAKE_CURRENT_BINARY_DIR}
           --java_out ${CMAKE_CURRENT_BINARY_DIR}
           --ignmsgs_out ${CMAKE_CURRENT_BINARY_DIR}
           --proto_path ${PROJECT_SOURCE_DIR} ${ABS_FIL}
      DEPENDS ${ABS_FIL} ign_msgs_gen
      COMMENT "Running C++, and Java protocol buffer compiler on ${FIL}"
      VERBATIM)
  else()
    list(APPEND PROTO_RB
      "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.rb")

    add_custom_command(
      OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.h"
        "${CMAKE_CURRENT_BINARY_DIR}/ignition/msgs/${FIL_WE}.pb.rb"

      COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --plugin=protoc-gen-ignmsgs=$<TARGET_FILE:ign_msgs_gen>
           --cpp_out=dllexport_decl=IGNITION_MSGS_VISIBLE:${CMAKE_CURRENT_BINARY_DIR}
           --java_out=${CMAKE_CURRENT_BINARY_DIR}
           --ruby_out=${CMAKE_CURRENT_BINARY_DIR}
           --ignmsgs_out ${CMAKE_CURRENT_BINARY_DIR}
           --proto_path ${PROJECT_SOURCE_DIR} ${ABS_FIL}
      DEPENDS ${ABS_FIL} ign_msgs_gen
      COMMENT "Running C++, Java, and Ruby protocol buffer compiler on ${FIL}"
      VERBATIM )
  endif()

endforeach()

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS}
  PROPERTIES GENERATED TRUE)

link_directories(${IGNITION-MATH_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
ign_add_library(${PROJECT_LIBRARY_TARGET_NAME}
  ${PROTO_SRCS} ${PROJECT_SOURCE_DIR}/src/Factory.cc
  ${PROJECT_SOURCE_DIR}/src/ign.cc
  ${PROJECT_SOURCE_DIR}/src/Utility.cc)
target_link_libraries(${PROJECT_LIBRARY_TARGET_NAME} ${PROTOBUF_LIBRARY}
  ${IGNITION-MATH_LIBRARIES})

if (UNIX)
  # Need to add default visibility to ignition-msgs
  get_target_property(current_property ${PROJECT_LIBRARY_TARGET_NAME}
    COMPILE_FLAGS)

  # property non-existent or empty
  if(NOT current_property)
    set_target_properties(${PROJECT_LIBRARY_TARGET_NAME}
      PROPERTIES GENERATED TRUE
      COMPILE_FLAGS "-fvisibility=default")
  else()
    set_target_properties(${PROJECT_LIBRARY_TARGET_NAME}
      PROPERTIES COMPILE_FLAGS
      "${current_property} -fvisibility=default")
  endif()
endif()

add_dependencies(${PROJECT_LIBRARY_TARGET_NAME} ign_msgs_gen)

set (ign_msgs_headers "" CACHE INTERNAL "Include dirs description")

foreach (hdr ${PROTO_HDRS})
  string (REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" hdr ${hdr})
  APPEND_TO_CACHED_STRING(ign_msgs_headers
    "Ignition messages" "#include <${hdr}>\n")
endforeach()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/ign_auto_headers.hh.in
  ${CMAKE_CURRENT_BINARY_DIR}/MessageTypes.hh)

ign_install_includes(
  "${INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_PROJECT_NAME}"
  ${CMAKE_CURRENT_BINARY_DIR}/MessageTypes.hh)

# When the minimum CMake required version will be >= 3.1
# we could use the target_compile_features() command
# to enable C++11 support in a platform-independent way.
if(NOT MSVC)
  target_compile_options(${PROJECT_LIBRARY_TARGET_NAME} PUBLIC "-std=c++11")
endif()

target_include_directories(${PROJECT_LIBRARY_TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR_FULL}>)

message(STATUS "Installing Ruby messages to ${RUBY_INSTALL_DIR}/ignition/msgs")
install(FILES ${PROTO_RB} DESTINATION ${RUBY_INSTALL_DIR}/ignition/msgs)

ign_install_includes(
  "${INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_PROJECT_NAME}" ${PROTO_HDRS})
ign_install_library(${PROJECT_LIBRARY_TARGET_NAME} ${PROJECT_EXPORT_NAME})
ign_install_includes(
  "${INCLUDE_INSTALL_DIR_POSTFIX}/ignition/${IGN_PROJECT_NAME}" ${msgs})
