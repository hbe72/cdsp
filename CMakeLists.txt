cmake_minimum_required(VERSION 3.2)
project(Cdsp)
include("cmake/common.cmake")

set(Cnl_DESTDIR ${CMAKE_BINARY_DIR}/install)
file(MAKE_DIRECTORY ${Cnl_DESTDIR})

message("-- CXX COMPILER = ${CMAKE_CXX_COMPILER}")
message("-- C COMPILER = ${CMAKE_C_COMPILER}")
message("-- INT128 = ${INT128}")
message("-- STD = ${STD}")
message("-- EXCEPTIONS = ${EXCEPTIONS}")

ExternalProject_Add(
        Cnl
        PREFIX ${CMAKE_BINARY_DIR}/Cnl
        GIT_REPOSITORY "https://github.com/johnmcfarlane/cnl.git"
        GIT_TAG "24867624ccb4ff260326df2e152479e56eb945fc"
        GIT_SHALLOW 1
        GIT_PROGRESS 1
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_INSTALL_PREFIX=${Cnl_DESTDIR} -DINT128=${INT128} -DSTD=${STD} -DEXCEPTIONS=${EXCEPTIONS}
)

# runs a suite of compile-time tests using `static_assert`
# and run-time tests using gtest
include(CTest)
add_subdirectory("test" EXCLUDE_FROM_ALL)

add_library(Cdsp INTERFACE)

install(DIRECTORY include/ DESTINATION include)

target_include_directories(
        Cdsp INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS Cdsp EXPORT CdspTargets)

install(EXPORT CdspTargets
    FILE CdspConfig.cmake
    NAMESPACE Cdsp::
    DESTINATION lib/cmake/cdsp)

install(DIRECTORY ${Cnl_DESTDIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX})
