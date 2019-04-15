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

set(CNL_GIT_TAG_DEFAULT b89764fb4845cc3a5e880e00d0c463520ee3ff92)
set(CNL_GIT_TAG_ENV $ENV{CDSP_CNL_GIT_TAG})
set(CNL_GIT_TAG "" CACHE BOOL "specify which revision of CNL to use")

if (CNL_GIT_TAG_ENV)
    set(CNL_GIT_TAG "${CNL_GIT_TAG_ENV}")
    message("Using CNL tag, ${CNL_GIT_TAG}, from environment variable, `CDSP_CNL_GIT_TAG`.")
elseif (CNL_GIT_TAG)
    message("Using CNL tag, ${CNL_GIT_TAG}, from CMake configuration `CNL_GIT_TAG`.")
else ()
    set(CNL_GIT_TAG "${CNL_GIT_TAG_DEFAULT}")
    message("Using CNL tag, ${CNL_GIT_TAG}, from project default, `CNL_GIT_TAG_DEFAULT`.")
endif ()

ExternalProject_Add(
        Cnl
        PREFIX ${CMAKE_BINARY_DIR}/Cnl
        GIT_REPOSITORY "https://github.com/johnmcfarlane/cnl.git"
        GIT_TAG "${CNL_GIT_TAG}"
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
