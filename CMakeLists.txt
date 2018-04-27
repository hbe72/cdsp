cmake_minimum_required(VERSION 3.7.2)
project(cnl)

# CNL

find_package(Cnl REQUIRED)

# Google Test

find_package(GTest REQUIRED)

# DSP tests

set(sample_dsp_sources
        test/basic_math.cpp
        test/biquad.cpp
        test/biquad_cascade.cpp
        test/complex.cpp
        test/complex_vector.cpp
        test/fft.cpp
        test/stft.cpp
        test/trig.cpp
        test/virtual_float.cpp)

include(CTest)

foreach(source ${sample_dsp_sources})
    string(REPLACE "\." "_" target "${source}")
    string(REPLACE "/" "-" target "${target}")
    add_executable(${target} ${source})
    add_test("${target}" "${target}")
    target_link_libraries(${target}
            Cnl::Cnl
            ${GTEST_LIBRARY}
            ${GTEST_MAIN_LIBRARY}
            general pthread)
    target_include_directories(
            ${target} PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
endforeach(source)
