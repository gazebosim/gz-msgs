\page install Installation

Next Tutorial: \ref cppgetstarted

These instructions are for installing only Ignition Messages.
If you're interested in using all the Ignition libraries, check out this [Ignition installation](https://ignitionrobotics.org/docs/latest/install).

We recommend following the Binary Installation instructions to get up and running as quickly and painlessly as possible.

The Source Installation instructions should be used if you need the very latest software improvements, you need to modify the code, or you plan to make a contribution.

# Binary Installation

## Ubuntu

On Ubuntu systems, `apt-get` can be used to install `ignition-msgs`:
```
sudo apt install libignition-msgs<#>-dev
```

Be sure to replace `<#>` with a number value, such as 2 or 3, depending on
which version you need.

## Windows

Install [Conda package management system](https://docs.conda.io/projects/conda/en/latest/user-guide/install/download.html).
Miniconda suffices.

Create if necessary, and activate a Conda environment:
```
conda create -n ign-ws
conda activate ign-ws
```

Install `ignition-msgs`:
```
conda install libignition-msgs<#> --channel conda-forge
```

Be sure to replace `<#>` with a number value, such as 2 or 3, depending on
which version you need.

# Source Installation

Source installation can be performed by first installing the necessary
prerequisites followed by building from source.

## Ubuntu

### Prerequisites

Install required dependencies as follows:
```
sudo apt-get install libprotobuf-dev protobuf-compiler libprotoc-dev libignition-math6-dev
```

### Building from Source

Standard installation can be performed in UNIX systems using the following
steps:
```
mkdir build/
cd build/
cmake ..
sudo make install
```

### Uninstallation

To uninstall the software installed with the previous steps:
```
cd build/
sudo make uninstall
```

## Windows

### Prerequisites

First, follow the [ign-cmake](https://github.com/ignitionrobotics/ign-cmake) tutorial for installing Conda, Visual Studio, CMake, etc., prerequisites, and creating a Conda environment.

Navigate to `condabin` if necessary to use the `conda` command (i.e., if Conda is not in your `PATH` environment variable. You can find the location of `condabin` in Anaconda Prompt, `where conda`).

Activate the Conda environment:
```
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

### Building from Source

This assumes you have created and activated a Conda environment while installing the Prerequisites.

1. Navigate to where you would like to build the library, and clone the repository.
  ```
  # Optionally, append `-b ign-msgs#` (replace # with a number) to check out a specific version
  git clone https://github.com/ignitionrobotics/ign-msgs.git
  ```

2. Configure and build
  ```
  cd ign-msgs
  mkdir build
  cd build
  cmake .. -DBUILD_TESTING=OFF  # Optionally, -DCMAKE_INSTALL_PREFIX=path\to\install
  cmake --build . --config Release
  ```

3. Optionally, install
  ```
  cmake --install . --config Release
  ```
