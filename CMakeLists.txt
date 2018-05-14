cmake_minimum_required(VERSION 3.7.2)
project(Cdsp)
include("cmake/common.cmake")

set(Cnl_DESTDIR ${CMAKE_BINARY_DIR}/install)
file(MAKE_DIRECTORY ${Cnl_DESTDIR})

ExternalProject_Add(
        Cnl
        PREFIX ${CMAKE_BINARY_DIR}/Cnl
        GIT_REPOSITORY "https://github.com/johnmcfarlane/cnl.git"
        GIT_TAG "develop"
        GIT_SHALLOW 1
        GIT_PROGRESS 1
        UPDATE_COMMAND ""
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${Cnl_DESTDIR}"
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
    NAMESPACE Cnl::
    DESTINATION lib/cmake/cdsp)

install(DIRECTORY ${Cnl_DESTDIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX})
