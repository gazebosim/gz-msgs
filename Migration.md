# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.


## Ignition Msgs 1.X to 2.X

### Modifications

### Deprecations

### Removals

1. The `Generator.hh` file is no longer installed. This file served only to
   make an internal protc plugin that customized the protobuf compiler output.
