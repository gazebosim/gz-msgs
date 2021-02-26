# Ignition Messages

**Protobuf messages and functions for robot applications.**

Ignition Messages is a component in the ignition framework, a set
of libraries designed to rapidly develop robot applications.

[http://ignitionrobotics.org](http://ignitionrobotics.org)

Test coverage:

[![codecov](https://codecov.io/gh/ignitionrobotics/ign-msgs/branch/master/graph/badge.svg)](https://codecov.io/gh/ignitionrobotics/ign-msgs)

## Installation

See the [installation tutorial](https://ignitionrobotics.org/api/msgs/6.2/index.html).

## Known issue of command line tools

In the event that the installation is a mix of Debian and from source, command
line tools from `ign-tools` may not work correctly.

A workaround for a single package is to define the environment variable
`IGN_CONFIG_PATH` to point to the location of the Ignition library installation,
where the YAML file for the package is found, such as
```
export IGN_CONFIG_PATH=/usr/local/share/ignition
```

However, that environment variable only takes a single path, which means if the
installations from source are in different locations, only one can be specified.

Another workaround for working with multiple Ignition libraries on the command
line is using symbolic links to each library's YAML file.
```
mkdir ~/.ignition/tools/configs -p
cd ~/.ignition/tools/configs/
ln -s /usr/local/share/ignition/fuel5.yaml .
ln -s /usr/local/share/ignition/transport9.yaml .
ln -s /usr/local/share/ignition/transportlog9.yaml .
...
export IGN_CONFIG_PATH=$HOME/.ignition/tools/configs
```

This issue is tracked [here](https://github.com/ignitionrobotics/ign-tools/issues/8).

