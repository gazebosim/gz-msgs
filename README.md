# Gazebo Messages: Protobuf messages and functions for robot applications

**Maintainer:** caguero AT openrobotics DOT org

[![GitHub open issues](https://img.shields.io/github/issues-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/gazebosim/gz-msgs/branch/ign-msgs8/graph/badge.svg)](https://codecov.io/gh/gazebosim/gz-msgs/branch/ign-msgs8)
Ubuntu Focal | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs8-focal-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs8-focal-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs8-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs8-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs8-windows7-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs8-windows7-amd64)

Gazebo Messages is a component in the [Gazebo](http://gazebosim.org)
framework, a set of libraries designed to rapidly develop robot applications.

## Installation

See the [installation tutorial](https://gazebosim.org/api/msgs/7.0/install.html).

## Known issue of command line tools

In the event that the installation is a mix of Debian and from source, command
line tools from `ign-tools` may not work correctly.

A workaround for a single package is to define the environment variable
`IGN_CONFIG_PATH` to point to the location of the Gazebo library installation,
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
ln -s /usr/local/share/ignition/fuel6.yaml .
ln -s /usr/local/share/ignition/transport11.yaml .
ln -s /usr/local/share/ignition/transportlog11.yaml .
...
export IGN_CONFIG_PATH=$HOME/.ignition/tools/configs
```

This issue is tracked [here](https://github.com/gazebosim/gz-tools/issues/8).

