# dsp

## Instructions

(Tested on Debian Stretch.)
In an empty workspace folder, run the following script:

```sh
#!/bin/bash

# clone the repositories
git clone git@github.com:hbe72/cnl --branch develop
git clone git@github.com:google/googletest --branch master
git clone git@github.com:johnmcfarlane/dsp

# create an env directory (for include, lib etc.)
ENV="$(pwd)/env"
mkdir -p $ENV

# configure, build and install CNL in env/
mkdir -p build/cnl
pushd build/cnl
cmake -DCMAKE_INSTALL_PREFIX=$ENV ../../cnl
cmake --build . -- -j 8 install
popd

# configure, build and install Google Test in env/
mkdir -p build/googletest
pushd build/googletest
cmake -DCMAKE_INSTALL_PREFIX=$ENV ../../googletest
cmake --build . -- -j 8 install
popd

# configure, build and test DSP
mkdir -p build/dsp
pushd build/dsp
cmake -DCMAKE_INSTALL_PREFIX=$ENV ../../dsp
cmake --build . -- -j 8
ctest
popd
```
