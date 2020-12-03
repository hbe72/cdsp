if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()
if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

project(cdsp VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.5.1)

unset(CDSP_STANDALONE)
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(CDSP_STANDALONE ON)
endif()

option(CDSP_ENABLE_TESTS "Set to true to enable tests" ${CDSP_STANDALONE})
if (CDSP_ENABLE_TESTS)
    include(CTest)
    add_subdirectory("test")
endif()

# the CDSP library
add_library(Cdsp INTERFACE)

target_include_directories(
        Cdsp INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

option(CDSP_ENABLE_INSTALL "Set to true to set install directives" ${CDSP_STANDALONE})
if (CDSP_ENABLE_INSTALL)
    install(TARGETS Cdsp EXPORT CdspTargets)
    install(DIRECTORY include/ DESTINATION include)
    install(EXPORT CdspTargets
            FILE CdspConfig.cmake
            NAMESPACE Cdsp::
            DESTINATION lib/cmake/cdsp)
endif()
