# Gazebo Messages: Protobuf messages and functions for robot applications

**Maintainer:** caguero AT openrobotics DOT org

[![GitHub open issues](https://img.shields.io/github/issues-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/gazebosim/gz-msgs.svg)](https://github.com/gazebosim/gz-msgs/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/gazebosim/gz-msgs/tree/gz-msgs10/graph/badge.svg)](https://codecov.io/gh/gazebosim/gz-msgs/tree/gz-msgs10)
Ubuntu Jammy  | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=gz_msgs-ci-gz-msgs10-jammy-amd64)](https://build.osrfoundation.org/job/gz_msgs-ci-gz-msgs10-jammy-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=gz_msgs-ci-gz-msgs10-homebrew-amd64)](https://build.osrfoundation.org/job/gz_msgs-ci-gz-msgs10-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=gz_msgs-10-win)](https://build.osrfoundation.org/job/gz_msgs-10-win)

Gazebo Messages is a component in the [Gazebo](http://gazebosim.org)
framework, a set of libraries designed to rapidly develop robot applications.

## Installation

See the [installation tutorial](https://gazebosim.org/api/msgs/10/install.html).

## Known issue of command line tools

In the event that the installation is a mix of Debian and from source, command
line tools from `gz-tools` may not work correctly.

A workaround for a single package is to define the environment variable
`GZ_CONFIG_PATH` to point to the location of the Gazebo library installation,
where the YAML file for the package is found, such as
```{.sh}
export GZ_CONFIG_PATH=/usr/local/share/gz
```

However, that environment variable only takes a single path, which means if the
installations from source are in different locations, only one can be specified.

Another workaround for working with multiple Gazebo libraries on the command
line is using symbolic links to each library's YAML file.
```{.sh}
mkdir ~/.gz/tools/configs -p
cd ~/.gz/tools/configs/
ln -s /usr/local/share/gz/fuel8.yaml .
ln -s /usr/local/share/gz/transport13.yaml .
ln -s /usr/local/share/gz/transportlog13.yaml .
...
export GZ_CONFIG_PATH=$HOME/.gz/tools/configs
```

This issue is tracked [here](https://github.com/gazebosim/gz-tools/issues/8).

