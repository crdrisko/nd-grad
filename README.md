# ND-Research

[![Build Status](https://travis-ci.com/crdrisko/ND-Research.svg?branch=master)](https://travis-ci.com/crdrisko/ND-Research)

Welcome to the ND-Research project!

<!--More detailed documentation for using nd-research can be found in the [`docs/primer.md`](https://github.com/crdrisko/nd-research/tree/master/docs/primer.md) file.

## Features

- ...-->

## Platforms

The ND-Research project has been built and tested on a number of operating systems, computer architectures, and compiler combinations.

- Mac OS X
- Linux
- Windows Subsystem for Linux (WSL)

**Coming Soon:**

- Windows
- Cygwin

## Requirements

The ND-Research project was designed to have as few external dependencies as possible so it could be easily built and used by other projects. The project requires:

- A C++17-standard-compliant compiler with support for the Standard Library.

- [Utilities-API](https://github.com/crdrisko/utilities-api) was used for a number of the utilities found throughout the various projects and scripts. More information about the API can be found in the repository's README.

- [CPP-Units](https://github.com/crdrisko/cpp-units) is a compile-time, header-only, API providing access to a number of physical quantities and units for cleaner code throughout the project. More information about the API can be found in the repository's README.

- [GoogleTest](https://github.com/google/googletest) was used for the testing all the source code in the project. Building and running all these tests is optional and more information can be found in the testing section of [`docs/build.md`](https://github.com/crdrisko/nd-research/tree/master/docs/build.md).

- The Bourne Again SHell (bash) is required if the use of any of the scripts in the `scripts` directory is desired. While other versions of bash may work, the lowest version of bash I have tested these scripts on is 3.2. Many, if not all, shell scripts in this repository are *not* compliant with the POSIX shell.

- Python3 is needed for a number of the analysis scripts. These scripts may work with python2, but I haven't actually tested for that.

### Build Requirements

- [CMake](https://cmake.org): Version 3.10.0 or higher. See the documentation in the [`docs/build.md`](https://github.com/crdrisko/nd-research/tree/master/docs/build.md) file for specific instructions on installing the project.

## License

Copyright (c) 2020 Cody R. Drisko. All rights reserved.

Licensed under the [MIT License](https://github.com/crdrisko/nd-research/blob/master/LICENSE).
