# Build and Installing ND-Research

## Installation

Using [CMake](https://cmake.org), the following commands can be run to install the repository:

```bash
git clone https://github.com/crdrisko/nd-research.git
mkdir build && cd build
cmake ../nd-research/.
make && [sudo] make install
```

By default, the project is installed in the `/usr/local` filesystem but can be changed with the `CMAKE_INSTALL_PREFIX` option.

## Testing

With each module in the project (ChargedRNEMD, ShiftXYZ, etc.), I have strived to provide ~100% unit test coverage for all functions. These tests can be found in the [`root/OpenMD/test`](https://github.com/crdrisko/cpp-units/tree/master/OpenMD/test) directory but do not get built by default. To turn on the testing features of the repository, add the `nd-research_build_tests` flag to the CMake instructions as shown in the code below.

```bash
## Same steps as before ...
cmake ../nd-research/. -Dnd-research_build_tests=ON
make && [sudo] make install

## Testing occurs in a separate, dedicated directory
cd OpenMD/test
ctest --output-on-failure
cd ../../
```

[GoogleTest](https://github.com/google/googletest), which is used as the unit test framework, will be installed as an external CMake project if the repository was not already found. The same is true for the [Utilities-API](https://github.com/crdrisko/utilities-api) and [CPP-Units](https://github.com/crdrisko/cpp-units) projects.
