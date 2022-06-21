# Gazebo Messages: Protobuf messages and functions for robot applications

**Maintainer:** caguero AT openrobotics DOT org

[![GitHub open issues](https://img.shields.io/github/issues-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/gazebosim/gz-msgs/branch/main/graph/badge.svg)](https://codecov.io/gh/gazebosim/gz-msgs)
Ubuntu Focal | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-main-focal-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-main-focal-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-main-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-main-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=gz_msgs-ci-win)](https://build.osrfoundation.org/job/gz_msgs-ci-win)

Gazebo Messages is a component in the [Ignition](http://gazebosim.org)
framework, a set of libraries designed to rapidly develop robot applications.

## Installation

See the [installation tutorial](https://gazebosim.org/api/msgs/7.0/install.html).

## Known issue of command line tools

In the event that the installation is a mix of Debian and from source, command
line tools from `ign-tools` may not work correctly.

A workaround for a single package is to define the environment variable
`GZ_CONFIG_PATH` to point to the location of the Ignition library installation,
where the YAML file for the package is found, such as
```
export GZ_CONFIG_PATH=/usr/local/share/gz
```

However, that environment variable only takes a single path, which means if the
installations from source are in different locations, only one can be specified.

Another workaround for working with multiple Ignition libraries on the command
line is using symbolic links to each library's YAML file.
```
mkdir ~/.ignition/tools/configs -p
cd ~/.ignition/tools/configs/
ln -s /usr/local/share/gz/fuel8.yaml .
ln -s /usr/local/share/gz/transport12.yaml .
ln -s /usr/local/share/gz/transportlog12.yaml .
...
export GZ_CONFIG_PATH=$HOME/.ignition/tools/configs
```

This issue is tracked [here](https://github.com/gazebosim/gz-tools/issues/8).

