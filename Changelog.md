## Ignition Msgs 5.x

### Ignition Msgs 5.x.x

### Ignition Msgs 5.1.0

1. Add ConvertPixelFormatType functions to Utility.hh
    * [BitBucket pull request 169](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/169)

### Ignition Msgs 5.0.0 (2019-12-09)

1. Add support for sdformat frame semantics
    * [BitBucket pull request 160](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/160)

1. Add emissive_map field to material.proto
    * [BitBucket pull request 155](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/155)

1. Add discovery message
    * [BitBucket pull request 159](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/159)

1. Deprecate all double fields in joint_cmd and pid, replace with Double
    * [BitBucket pull request 162](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/162)

1. Factory relative to
    * [BitBucket pull request 163](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/163)

1. Added `fuel_metadata.proto`, `version.proto`, `version_range.proto`, and `versioned_name.proto` message files. Added conversion functions to/from the model.config/metadata.pbtxt formats.
    * [BitBucket pull request 157](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/157)


### Ignition Msgs 4.x.x (202X-XX-XX)

### Ignition Msgs 4.8.0 (2020-04-09)

1. Add SdfGeneratorConfig message containing configuration options for generating SDFormat from currently loaded worlds
    * [BitBucket pull request 174](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/174)

1. Fix linking order of Protocol Buffers static libraries on GCC
    * [BitBucket pull request 151](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/151)

1. Ignore deprecation warnings on generated code
    * [BitBucket pull request 170](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/170)

### Ignition Msgs 4.7.0 (2019-08-22)

1. Add video record message
    * [BitBucket pull request 149](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/149)

### Ignition Msgs 4.6.0 (2019-08-16)

1. Add Actor message
    * [BitBucket pull request 147](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/147)

### Ignition Msgs 4.5.0 (2019-07-19)

1. Add battery state message
    * [BitBucket pull request 145](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/145)

### Ignition Msgs 4.4.0 (2019-07-16)

1. Added SerializedEntityMap, SerializedStateMap, and SerializedStepMap
   messages which match SerializedEntity, SerializedState, and SerializedStep messages except that the former uses `map` data structures.
    * [BitBucket pull request 143](https://github.com/ignitionrobotics/ign-common/pull-requests/143)

### Ignition Msgs 4.2.0

1. Added odometry message
    * [BitBucket pull request 137](https://github.com/ignitionrobotics/ign-common/pull-requests/137)

### Ignition Msgs 4.1.0

1. Added camera info message
    * [BitBucket pull request 136](https://github.com/ignitionrobotics/ign-common/pull-requests/136)

### Ignition Msgs 4.0.0 (2019-05-20)

1. Add world stats to packet message.
    * [BitBucket pull request 125](https://github.com/ignitionrobotics/ign-common/pull-requests/125)

1. Deprecating `raysensor.proto`, and replacing with `lidar_sensor.proto`.
    * [BitBucket pull request 124](https://github.com/ignitionrobotics/ign-common/pull-requests/124)

1. Added orientation reference frame information to `imu_sensor.proto`.
    * [BitBucket pull request 121](https://github.com/ignitionrobotics/ign-common/pull-requests/121)

1. New actuators `actuators.proto` message.
    * [BitBucket pull request 123](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/123)
    * [BitBucket pull request 129](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/129)

1. Added Physically Based Rendering (PBR) message to `material.proto`
    * [BitBucket pull request 120](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/120)

1. Corrected `BAYER_RGGR8` to `BAYER_BGGR8` in `PixelFormatType` located in
`proto/ignition/msgs/image.proto`.
    * [BitBucket pull request 118](https://github.com/ignitionrobotics/ign-common/pull-requests/118)

1. Adding `dynamic_bias_stddev` and `dynamic_bias_correlation_time` sensor noise parameters.
    * [BitBucket pull request 117](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/117)

1. Added `fluid_pressure.proto` and `air_pressure_sensor.proto`.
    * [BitBucket pull request 116](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/116)

1. Added `step_size` to `WorldStatistics` and `SerializedStep`
    * [BitBucket pull request 122](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/122)

1. Added an `altimeter_sensor.proto` message that encapsulates information
   about an altimeter sensor.
    * [BitBucket pull request 114](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/114)

1. Added a `magnetometer_sensor.proto` message that encapsulates information
   about  a magnetometer sensor.
    * [BitBucket pull request 113](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/113)

1. image: `pixel_format` field is deprecated, use `pixel_format_type` with enum `PixelFormatType` instead.
    * [BitBucket pull request 106](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/106)
    * [BitBucket pull request 95](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/95)

1. Updated `model.proto` with more documentation. Position, velocity, force,
   and acceleration information for joint have been moved to the `axis.proto`
   message, see the Migration guide. The `ign.hh` header file is no longer
   installed.
    * [BitBucket pull request 104](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/104)

1. Change serialized field from string to bytes.
    * [BitBucket pull request 102](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/102)

1. Install ruby files into versioned folder
    * [BitBucket pull request 109](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/109)
    * [Issue 24](https://github.com/ignitionrobotics/ign-msgs/issues/24)
    * [Issue 27](https://github.com/ignitionrobotics/ign-msgs/issues/27)

## Ignition Msgs 3.x

### Ignition Msgs 3.x.x

1. Install ruby files into versioned folder
    * [BitBucket pull request 111](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/111)
    * [Issue 24](https://github.com/ignitionrobotics/ign-msgs/issues/24)
    * [Issue 27](https://github.com/ignitionrobotics/ign-msgs/issues/27)

1. Fix linking order of Protocol Buffers static libraries on GCC
    * [BitBucket pull request 151](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/151)

### Ignition Msgs 3.2.0

1. Added Pose_V, Time, and Clock fields to packet.proto
    * [BitBucket pull request 108](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/108)

### Ignition Msgs 3.1.0

1. Added serialized messages: SerializedState, SerializedEntity, SerializedComponent
    * [BitBucket pull request 99](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/99)

1. image.proto: add `PixelFormatType` enum, copied from `ignition::common::Image::PixelFormatType`
    * [BitBucket pull request 97](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/97)


### Ignition Msgs 3.0.0

1. axis\_aligned\_box: new message and conversion functions
    * [BitBucket pull request 91](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/91)

1. contacts: use Entity instead of string to specify entities in contact
    * [BitBucket pull request 90](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/90)

1. entity: new message to uniquely identify an entity
    * [BitBucket pull request 87](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/87)

1. entity\_factory: refactor message, remove edit\_name field
    * [BitBucket pull request 86](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/86)
    * [Issue 25](https://github.com/ignitionrobotics/ign-msgs/issues/25)

1. Add twist message
    * [BitBucket pull request 83](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/83)

1. Update light msgs fields
    * [BitBucket pull request 78](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/78)

1. Combine docs
    * [BitBucket pull request 75](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/75)

1. configure.bat: don't need to list recursive dependencies
    * [BitBucket pull request 74](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/74)

1. Update gtest
    * [BitBucket pull request 73](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/73)

1. Upgrade to protobuf3
    * [BitBucket pull request 69](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/69)

1. Fix ruby message generation.
    * [BitBucket pull request 47](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/47)


## Ignition Msgs 2.x

### Ignition Msgs 2.x.x

1. Fix linking order of Protocol Buffers static libraries on GCC
    * [BitBucket pull request 151](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/151)

### Ignition Msgs 2.1.0

1. Upgrade to ign-math6
    * [BitBucket pull request 138](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/138)


### Ignition Msgs 2.0.0

1. sonar: add geometry field
    * [BitBucket pull request 82](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/82)

1. log\_control, log\_status: add record\_resources bool to match osrf/gazebo PR 3008
    * [BitBucket pull request 76](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/76)
    * [osrf/gazebo Pull request 3008](https://osrf-migration.github.io/gazebo-gh-pages/#!/osrf/gazebo/pull-requests/3008)

1. Added inline versioned namespace. Generator.hh is no longer installed
    * [BitBucket pull request 59](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/59)

1. Upgrade to ign-cmake1
    * [BitBucket pull request 55](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/55)

1. Extend Factory class
    * [BitBucket pull request 61](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/61)
    * [BitBucket pull request 66](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/66)

1. Add real\_time\_factor field to WorldStatistics
    * [BitBucket pull request 67](https://osrf-migration.github.io/ignition-gh-pages/#!/ignitionrobotics/ign-msgs/pull-requests/67)

