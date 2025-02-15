[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/crdrisko/nd-grad?include_prereleases)](https://github.com/crdrisko/nd-grad/releases) [![DOI](https://zenodo.org/badge/232623725.svg)](https://doi.org/10.5281/zenodo.14876051)

# ND-Grad

Welcome to the ND-Grad project! This repository is a merger of the formerly separate ND-Research and ND-Coursework projects. Because these repositories were so closely related, it makes sense to maintain and release them together.

## Getting started

Information for getting started using ND-Grad is available in the [`docs/primer.md`](docs/primer.md) documentation.

More detailed documentation for nd-research and nd-coursework can be found in the interior [`nd-research/README.md`](nd-research/README.md) and [`nd-coursework/README.md`](nd-coursework/README.md) files, respectively.

## Features

- Post-processing analysis utilities and applications for data files generated through [OpenMD](https://github.com/OpenMD/OpenMD).

- Scripts for the automation of common tasks associated with my research.

- A random-sampling algorithm for the construction of Potential Energy Surfaces (PES) using [GAMESS](https://www.msg.chem.iastate.edu/gamess).

- Miscellaneous code associated with coursework and assignments during my time in graduate school.

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

- The Bourne Again SHell (bash) is required to use of many of the scripts. While other versions of bash may work, the lowest version of bash I have tested these scripts on is 3.2. Many, if not all, shell scripts in this repository are *not* compliant with the POSIX shell.

- Python3 is needed for a number of the analysis scripts. While these scripts may work with python2, I haven't actually tested for that.

### Build Requirements

- [CMake](https://cmake.org): Version 3.10.0 or higher. See the documentation in the [`docs/build.md`](https://github.com/crdrisko/nd-research/tree/master/docs/build.md) file for specific instructions on installing the project.

## License

Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.

Licensed under the [MIT License](https://github.com/crdrisko/nd-research/blob/master/LICENSE).
