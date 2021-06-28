# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.

## Ignition Msgs 4.X to 5.X

### Modifications


### Deprecations

1. **axis.proto**
    + The `use_parent_model_frame` field is deprecated, use `xyz_expressed_in` instead. Setting `xyz_expressed_in = "__model__"` is equivalent to`use_parent_model_frame = true` and leaving `xyz_expressed_in` empty is equivalent to `use_parent_model_frame = false`

## Ignition Msgs 3.X to 4.X

### Modifications

1. **image.proto**
    + Corrected `BAYER_RGGR8` to `BAYER_BGGR8` in `PixelFormatType`.

1. **joint.proto**
    + The `axis.proto` message contains joint position, velocity, force, and
    acceleration information.

1. **serialized.proto**
    + `SerializedComponent`'s `component` field type changed from `string` to `bytes`.

1. **sensor.proto**
    + Deprecating `RaySensor`, and replacing with `LidarSensor`.

### Deprecations

1. **joint.proto**
    + The `angle` field is deprecated, use `position` in the axis.proto
    message instead.
    + The `velocity` field is deprecated, use `velocity` in the axis.proto
    message instead.

1. **image.proto**
    + `pixel_format` field is deprecated, use `pixel_format_type` with enum `PixelFormatType` instead.

### Removals

1.  **include/ignition/msgs/ign.hh** is no longer installed.

## Ignition Msgs 2.X to 3.X

### Additions

1. **axis\_aligned\_box.proto**
    + New message for axis-aligned bounding boxes.

1. **entity.proto**
    + New message to uniquely identify an entity.

1. **entity\_factory.proto**
    + Add `Model` field to allow model insertion.

1. **light.proto**
    + Add `id`, `parent_id` fields.

1. **link.proto**
    + Add repeated `light` field.

1. **twist.proto**
    + New message for storing linear and angular velocity.

1. **Utility.hh**
    + Conversion functions for `axis_aligned_box.proto`.

### Modifications

1. Use ignition-cmake2 and ignition-math6.

1. Use protobuf3 for all messages.

1. **contacts.proto**
    + Use `Entity` instead of string to specify entities in contact.

1. **entity\_factory.proto**
    + Rename `clone_model_name` field to `clone_name`.
    + Remove `edit_name` field.
    + Use `oneof` to indicate only one method can be used at a time.

### Deprecations

### Removals


## Ignition Msgs 2.0 to 2.1

### Modifications

1. Use `ignition-math6` instead of `ignition-math5`.
  This implies an indirect dependency on `ignition-cmake2` and cmake 3.10.2,
  which are not available on Ubuntu Xenial, so migration to Ubuntu Bionic may
  be required.

## Ignition Msgs 1.X to 2.0

### Additions

1. **log\_control.proto**
    + Add `record_resources` bool to match osrf/gazebo PR 3008.

1. **log\_status.proto**
    + Add `record_resources` bool to match osrf/gazebo PR 3008.

1. **sonar.proto**
    + Add `geometry` field.

1. **world\_statistics.proto**
    + Add `real_time_factor` field.

### Modifications

1. Use ignition-cmake1 and ignition-math5.

1. Use inline versioned namespace.

### Deprecations

### Removals

1. **Generator.hh**
    + This file is no longer installed. It served only to make an internal
      protc plugin that customized the protobuf compiler output.
