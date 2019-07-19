## Ignition Msgs 4.x

### Ignition Msgs 4.x.x

### Ignition Msgs 4.5.0 (2019-07-19)

1. Add battery state message
    * [Pull request 145](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-requests/145)

### Ignition Msgs 4.4.0 (2019-07-16)

1. Added SerializedEntityMap, SerializedStateMap, and SerializedStepMap
   messages which match SerializedEntity, SerializedState, and SerializedStep messages except that the former uses `map` data structures.
    * [Pull request 143](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/143)

### Ignition Msgs 4.2.0

1. Added odometry message
    * [Pull request 137](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/137)

### Ignition Msgs 4.1.0

1. Added camera info message
    * [Pull request 136](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/136)

### Ignition Msgs 4.0.0 (2019-05-20)

1. Add world stats to packet message.
    * [Pull request 125](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/125)

1. Deprecating `raysensor.proto`, and replacing with `lidar_sensor.proto`.
    * [Pull request 124](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/124)

1. Added orientation reference frame information to `imu_sensor.proto`.
    * [Pull request 121](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/121)

1. New actuators `actuators.proto` message.
    * [Pull request 123](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/123)
    * [Pull request 129](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/129)

1. Added Physically Based Rendering (PBR) message to `material.proto`
    * [Pull request 120](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/120)

1. Corrected `BAYER_RGGR8` to `BAYER_BGGR8` in `PixelFormatType` located in
`proto/ignition/msgs/image.proto`.
    * [Pull request 118](https://bitbucket.org/ignitionrobotics/ign-common/pull-requests/118)

1. Adding `dynamic_bias_stddev` and `dynamic_bias_correlation_time` sensor noise parameters.
    * [Pull request 117](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/117)

1. Added `fluid_pressure.proto` and `air_pressure_sensor.proto`.
    * [Pull request 116](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/116)

1. Added `step_size` to `WorldStatistics` and `SerializedStep`
    * [Pull request 122](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/122)

1. Added an `altimeter_sensor.proto` message that encapsulates information
   about an altimeter sensor.
    * [Pull request 114](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/114)

1. Added a `magnetometer_sensor.proto` message that encapsulates information
   about  a magnetometer sensor.
    * [Pull request 113](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/113)

1. image: `pixel_format` field is deprecated, use `pixel_format_type` with enum `PixelFormatType` instead.
    * [Pull request 106](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/106)
    * [Pull request 95](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/95)

1. Updated `model.proto` with more documentation. Position, velocity, force,
   and acceleration information for joint have been moved to the `axis.proto`
   message, see the Migration guide. The `ign.hh` header file is no longer
   installed.
    * [Pull request 104](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/104)

1. Change serialized field from string to bytes.
    * [Pull request 102](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/102)

1. Install ruby files into versioned folder
    * [Pull request 109](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/109)
    * [Issue 24](https://bitbucket.org/ignitionrobotics/ign-msgs/issues/24)
    * [Issue 27](https://bitbucket.org/ignitionrobotics/ign-msgs/issues/27)

## Ignition Msgs 3.x

### Ignition Msgs 3.x.x

1. Install ruby files into versioned folder
    * [Pull request 111](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/111)
    * [Issue 24](https://bitbucket.org/ignitionrobotics/ign-msgs/issues/24)
    * [Issue 27](https://bitbucket.org/ignitionrobotics/ign-msgs/issues/27)

### Ignition Msgs 3.2.0

1. Added Pose_V, Time, and Clock fields to packet.proto
    * [Pull request 108](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/108)

### Ignition Msgs 3.1.0

1. Added serialized messages: SerializedState, SerializedEntity, SerializedComponent
    * [Pull request 99](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/99)

1. image.proto: add `PixelFormatType` enum, copied from `ignition::common::Image::PixelFormatType`
    * [Pull request 97](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/97)


### Ignition Msgs 3.0.0

1. axis\_aligned\_box: new message and conversion functions
    * [Pull request 91](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/91)

1. contacts: use Entity instead of string to specify entities in contact
    * [Pull request 90](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/90)

1. entity: new message to uniquely identify an entity
    * [Pull request 87](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/87)

1. entity\_factory: refactor message, remove edit\_name field
    * [Pull request 86](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/86)
    * [Issue 25](https://bitbucket.org/ignitionrobotics/ign-msgs/issues/25)

1. Add twist message
    * [Pull request 83](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/83)

1. Update light msgs fields
    * [Pull request 78](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/78)

1. Combine docs
    * [Pull request 75](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/75)

1. configure.bat: don't need to list recursive dependencies
    * [Pull request 74](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/74)

1. Update gtest
    * [Pull request 73](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/73)

1. Upgrade to protobuf3
    * [Pull request 69](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/69)

1. Fix ruby message generation.
    * [Pull request 47](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/47)


## Ignition Msgs 2.x

### Ignition Msgs 2.x.x


### Ignition Msgs 2.0.0

1. sonar: add geometry field
    * [Pull request 82](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/82)

1. log\_control, log\_status: add record\_resources bool to match osrf/gazebo PR 3008
    * [Pull request 76](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/76)
    * [osrf/gazebo Pull request 3008](https://bitbucket.org/osrf/gazebo/pull-request/3008)

1. Added inline versioned namespace. Generator.hh is no longer installed
    * [Pull request 59](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/59)

1. Upgrade to ign-cmake1
    * [Pull request 55](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/55)

1. Extend Factory class
    * [Pull request 61](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/61)
    * [Pull request 66](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/66)

1. Add real\_time\_factor field to WorldStatistics
    * [Pull request 67](https://bitbucket.org/ignitionrobotics/ign-msgs/pull-request/67)

