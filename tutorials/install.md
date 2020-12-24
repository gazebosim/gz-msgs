\page install Installation

Next Tutorial: \ref cppgetstarted

These instructions are for installing only Ignition Messages.
If you're interested in using all the Ignition libraries, check out this [Ignition installation](https://ignitionrobotics.org/docs/latest/install).

# Dependencies

## UNIX

Install required dependencies as follows:

```
sudo apt-get install libprotobuf-dev protobuf-compiler libprotoc-dev libignition-math6-dev
```

## Windows

First, follow the [ign-cmake](https://github.com/ignitionrobotics/ign-cmake) tutorial for installing Conda, Visual Studio, CMake, etc., prerequisites, and creating a Conda environment.

Create if necessary, and activate a Conda environment:

```
conda create -n ign-ws
conda activate ign-ws
```

Install prerequisites:

```
conda install tinyxml2 protobuf --channel conda-forge
```

Install Ignition dependencies:

You can view lists of dependencies:

```
conda search libignition-msgs* --channel conda-forge --info
```

Install dependencies, replacing `<#>` with the desired versions:

```
conda install libignition-cmake<#> libignition-math<#> libignition-tools<#> --channel conda-forge
```

# Installation

## UNIX

Standard installation can be performed in UNIX systems using the following
steps:

```
mkdir build/
cd build/
cmake ..
sudo make install
```

## Windows

This assumes you have created and activated a Conda environment while installing the Dependencies.

1. Configure and build

    ```
    mkdir build
    cd build
    cmake .. -DBUILD_TESTING=OFF  # Optionally, -DCMAKE_INSTALL_PREFIX=path\to\install
    cmake --build . --config Release
    ```

1. Optionally, install

    ```
    cmake --install . --config Release
    ```

# Uninstallation

## UNIX

To uninstall the software installed with the previous steps:

```
cd build/
sudo make uninstall
```
