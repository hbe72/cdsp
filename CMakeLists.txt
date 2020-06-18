if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()
if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

project(cdsp VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.5.1)

include(CTest)
add_subdirectory("test")

# the CDSP library
add_library(Cdsp INTERFACE)

target_include_directories(
        Cdsp INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS Cdsp EXPORT CdspTargets)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT CdspTargets
        FILE CdspConfig.cmake
        NAMESPACE Cdsp::
        DESTINATION lib/cmake/cdsp)