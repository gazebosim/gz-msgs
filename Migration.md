# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.


## Ignition Msgs 2.0 to 2.1

### Modifications

1. Use `ignition-math6` instead of `ignition-math5`.
  This implies an indirect dependency on `ignition-cmake2` and cmake 3.10.2,
  which are not available on Ubuntu Xenial, so migration to Ubuntu Bionic may
  be required.

## Ignition Msgs 1.X to 2.0

### Modifications

1. Use `ignition-cmake1` and `ignition-math5` instead of `ignition-cmake0` and `ignition-math4`.

### Deprecations

### Removals

1. The `Generator.hh` file is no longer installed. This file served only to
   make an internal protc plugin that customized the protobuf compiler output.
