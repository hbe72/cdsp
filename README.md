# CDSP - Compositional DSP Library for C++
| develop @ Travis-CI <br/> (macOS & Linux)| develop @ Appveyor <br/> (Windows) |
| ------------- | ------------- |
| [![Build Status](https://travis-ci.org/hbe72/cdsp.svg?branch=develop)](https://travis-ci.org/hbe72/cdsp) | [![Build status](https://ci.appveyor.com/api/projects/status/1q4y3h8vy8t1kn5e/branch/develop?svg=true)](https://ci.appveyor.com/project/hbe72/cdsp/branch/develop)|

CDSP is a header only DSP library written with
[CNL](https://github.com/johnmcfarlane/cnl) aiming for floating point and 
fixed-point implementation of typical DSP kernels.

Algorithm designers often start with [Matlab](https://www.mathworks.com/), 
[Scipy](https://www.scipy.org), [R](https://www.r-project.org/) or maybe
[Julia](https://julialang.org/) and get the algorithm designed on very high 
level with a floating-point datatype. For real-time applications the final 
target is often fixed-point DSP, FPGA or ASIC. Manual porting of the algorithm 
to fixed-point is needed which can lead to three separate algorithm source 
codes: original algorithm in floating-point, fixed-point design of the same and
the final implementation on the target. Keeping them in synchronization is a
nightmare.

CDSP library shows how with [CNL](https://github.com/johnmcfarlane/cnl) single 
source code can provide full implementation. Minimally, CDSP can provide both 
floating-point and fixed-point designs from the same source code. In the case 
compliant C++ compiler exists for the target the final implementation is done 
as well.

CDSP fixed-point implementations are measured against their floating point 
counterparts in terms of numerical accuracy. At this point performance with 
Cirrus ADSP2 fixed-point datatypes have been tested and separately verified 
against native Cirrus ADSP2 implementation. Composing new datatype 
with [CNL](https://github.com/johnmcfarlane/cnl) and specializing the lowest
level of core CDSP kernels is quite straight forward to support other 
architectures such as Qualcomm, TI DSPs and other application specific 
processors as well as for ASIC implementation.

## Requirements 

Requirements are the same as with [CNL](https://github.com/johnmcfarlane/cnl).
CDSP pulls CNL from it's conan package.
* [Cmake](https://cmake.org/) 3.5.1
* [Conan](https://conan.io/downloads.html)

### Linux
Tested on [Travis] (https://travis-ci.org/github/hbe72/cdsp)

### Mac
Tested on [Travis] (https://travis-ci.org/github/hbe72/cdsp).
For missing packages (compilers) please use [Homebrew](https://brew.sh/).

### Windows
Tested on [AppVeyor](https://ci.appveyor.com/project/hbe72/cdsp)

## Instructions
### Download
The library is hosted on [GitHub](https://github.com/hbe72/cdsp)
```shell
git clone https://github.com/hbe72/cdsp.git
```

### Build
Generate the build system and install cdsp
```shell
cd cdsp 
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/directory/to/install -DCMAKE_BUILD_TYPE=Release
cmake --build . --target install
```

### Test    
1. Conan for essential dependencies:
    ```shell
    conan remote add --force johnmcfarlane/cnl https://api.bintray.com/conan/johnmcfarlane/cnl
    conan profile new --detect --force default
    ```
    For GCC:

    ```shell
    conan profile update settings.compiler.libcxx=libstdc++11 default
    ```

    On OSX for clang or for apple-clang:
    ```shell
    conan profile update settings.compiler.libcxx=libc++ default
    ```

    On Windows:
    ```shell
    conan profile update settings.compiler="Visual Studio" default
    conan profile update settings.os=Windows default
    ```

    And finally install the dependencies:
    ```shell
    conan install --build=missing ..
    ```

2. Configure the build with apprpriate toolchain.
    With GCC:
   ```shell
   cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../test/cmake/toolchain/gcc.cmake -DCNL_SANITIZE=OFF -DCMAKE_PROJECT_cdsp_INCLUDE:FILEPATH="$(pwd)"/conan_paths.cmake ..
   ```
   or with Clang:
   ```shell
   cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../test/cmake/toolchain/clang.cmake -DCNL_SANITIZE=OFF -DCMAKE_PROJECT_cdsp_INCLUDE:FILEPATH="$(pwd)"/conan_paths.cmake ..
   ```
   or with MSVC:
   ```shell
   cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../test/cmake/toolchain/msvc.cmake -DCNL_SANITIZE=OFF -DCMAKE_PROJECT_cdsp_INCLUDE:FILEPATH="$(pwd)"/conan_paths.cmake ..
   ```
   
3. Build tests:
   ```shell
   cmake --build . --target test-all
   ```

4. Run tests:
   ```shell
   ctest -R test-unit
   ```
