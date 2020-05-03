# Ignition Messages

**Protobuf messages and functions for robot applications.**

Ignition Messages is a component in the ignition framework, a set
of libraries designed to rapidly develop robot applications.

[http://ignitionrobotics.org](http://ignitionrobotics.org)

Test coverage:

[![codecov](https://codecov.io/gh/ignitionrobotics/ign-msgs/branch/master/graph/badge.svg)](https://codecov.io/gh/ignitionrobotics/ign-msgs)

## Dependencies

Install required dependencies as follows:

    sudo apt-get install libprotobuf-dev protobuf-compiler libprotoc-dev libignition-math4-dev

## Installation

Standard installation can be performed in UNIX systems using the following
steps:

    mkdir build/
    cd build/
    cmake ..
    sudo make install

## Uninstallation

To uninstall the software installed with the previous steps:

    cd build/
    sudo make uninstall

## Test

Run tests as follows:

    make test

Tests are automatically built. To disable them, run `cmake` as follows:

    cmake .. -DENABLE_TESTS_COMPILATION=false

### Test coverage

To run test coverage:

1. Install LCOV

        sudo apt-get install lcov

1. Build with coverage

        cd build/
        cmake .. -DCMAKE_BUILD_TYPE=coverage
        make

1. Run tests

        make test

1. Generate coverage

        make coverage

1. View results

        firefox coverage/index.html

## Create Documentation & Release

1. Build documentation

```
cd build
make doc
```

1. Upload documentation to ignitionrobotics.org.

```
cd build
sh upload.sh
```

1. If you're creating a new release, then tell ignitionrobotics.org about
   the new version. For example:

```
curl -k -X POST -d '{"libName":"msgs", "version":"1.0.0", "releaseDate":"2017-10-09T12:10:13+02:00","password":"secret"}' https://api.ignitionrobotics.org/1.0/versions
```

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
ln -s /usr/local/share/ignition/fuel4.yaml .
ln -s /usr/local/share/ignition/transport7.yaml .
ln -s /usr/local/share/ignition/transportlog7.yaml .
...
export IGN_CONFIG_PATH=$HOME/.ignition/tools/configs
```

This issue is tracked [here](https://github.com/ignitionrobotics/ign-tools/issues/8).

