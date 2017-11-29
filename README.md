# Ignition Messages

** Ignition Message protobuf messages and functions for robot applications.**

Ignition Messages is a component in the ignition framework, a set
of libraries designed to rapidly develop robot applications.

[http://ignitionrobotics.org](http://ignitionrobotics.org)

Test coverage:

[![codecov](https://codecov.io/bb/ignitionrobotics/ign-msgs/branch/master/graph/badge.svg)](https://codecov.io/bb/ignitionrobotics/ign-msgs)

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

> Tests are automatically built. To disable them, run `cmake` as follows:

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

