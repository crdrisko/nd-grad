# ND-Research

### Build Status - Version 1.0.0

[![Build Status](https://travis-ci.com/crdrisko/ND-Research.svg?branch=master)](https://travis-ci.com/crdrisko/ND-Research)

## Platforms

The ND-Research repository has been built and tested on a number of operating systems, computer architectures, and compiler combinations.

- Mac OS X

## Requirements

ND-Research requires

- [CMake](https://cmake.org): Version 3.10.0 or higher.

- A C++17-standard-compliant compiler.

- [Utilities-API](https://github.com/crdrisko/utilities-api): used for a number of the utilities found throughout the various projects and scripts. More information about the API can be found in the repository's README. The `ci/install-utilities-api.sh` script can be used to install the repository where desired.

Optional:

- [GoogleTest](https://github.com/google/googletest): used for the testing of all source code in the project (see the `test` directory). The `ci/install-gtest.sh` script in the utilities-api repository (see above) can be used to install GoogleTest where desired. Running all these tests is optional and can be turned on using the `-Dbuild_all_tests=ON` flag during the build.

- The Bourne Again SHell (bash) is required if the use of any of the scripts in the `scripts` directory is desired. While other versions of bash may work, the lowest version of bash I have tested these scripts on is 3.2. Many, if not all, shell scripts in this repository are *not* compliant with the POSIX shell.

## Installation

Installation of ND-Research is designed to be as easy as possible. Using CMake, the following commands can be run:

```bash
$ git clone https://github.com/crdrisko/nd-research.git
$ mkdir build && cd build
$ cmake ../nd-research/.
$ make && [sudo] make install
```

- NOTE: the default install directory is `/usr/local`.
