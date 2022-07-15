# Gazebo Messages: Protobuf messages and functions for robot applications

**Maintainer:** caguero AT openrobotics DOT org

[![GitHub open issues](https://img.shields.io/github/issues-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/gazebosim/gz-msgs/branch/ign-msgs5/graph/badge.svg)](https://codecov.io/gh/gazebosim/gz-msgs/branch/ign-msgs5)
Ubuntu Bionic | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs5-bionic-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs5-bionic-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs5-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs5-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_msgs-ci-ign-msgs5-windows7-amd64)](https://build.osrfoundation.org/job/ignition_msgs-ci-ign-msgs5-windows7-amd64)

Gazebo Messages is a component in the [Gazebo](http://gazebosim.org)
framework, a set of libraries designed to rapidly develop robot applications.

## Installation

See the [installation tutorial](https://gazebosim.org/api/msgs/6.2/index.html).

## Known issue of command line tools

In the event that the installation is a mix of Debian and from source, command
line tools from `ign-tools` may not work correctly.

A workaround is to define the environment variable
`IGN_CONFIG_PATH` to point to the location of the Gazebo library installation,
where the YAML file for the package is found, such as
```
export IGN_CONFIG_PATH=/usr/local/share/ignition
```

This issue is tracked [here](https://github.com/gazebosim/gz-tools/issues/61).
