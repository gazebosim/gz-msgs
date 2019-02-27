# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.


## Ignition Msgs 1.X to 2.X

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
