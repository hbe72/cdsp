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
processors.

## Requirements 

Requirements are the same as with [CNL](https://github.com/johnmcfarlane/cnl).
CDSP installs [CNL](https://github.com/johnmcfarlane/cnl) and CDSP side-by-side
and the only prerequisites are listed below.

### Linux
Requires:
* GCC 5.1 / Clang 3.5
* [Cmake](https://cmake.org/) 3.2.2

Optional:
* [Boost](https://www.boost.org/) - for multiprecision support with [CNL](https://github.com/johnmcfarlane/cnl)
* [Doxygen](https://www.doxygen.org/) - generates documentation in the doc/gh-pages directory

### Mac
See the instructions for Linux. Works similarly. 
For missing packages please use [Homebrew](https://brew.sh/).

### Windows
* MSBuild 15.0 (VS 2017)
* [Cmake](https://cmake.org/) 3.8.0

## Instructions
### Download
The library is hosted on [GitHub](https://github.com/hbe72/dsp)
```
cd /some/directory
git clone https://github.com/hbe72/cdsp.git
```

### Build
1. Generate the build system
    ```
    mkdir build
    cd build
    cmake /some/directory/cdsp -DCMAKE_INSTALL_PREFIX=/directory/to/install 
    ```     
    
2. Build tests:
    * Linux and Mac parallel with 8 cores
    ```
    cmake --build . --target Tests -- -j8
    ```
    * Windows
    ```
    cmake --build . --target test/Tests
    ```
3. Run the tests
    ```
    ctest
    ```
4. Install 
    
    If you want to install the CDSP and CNL libraries to location specified by
    CMAKE_INSTALL_PREFIX. 
    ```
    cmake --build . --target install 
    ```

    By default CDSP and CNL install to /usr/local. 
