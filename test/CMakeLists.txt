include("../cmake/common.cmake")

# DSP tests
set(sample_cdsp_sources
        basic_math.cpp
        biquad.cpp
        biquad_cascade.cpp
        complex.cpp
        complex_vector.cpp
        fft.cpp
        stft.cpp
        trig.cpp
        virtual_float.cpp
        )

######################################################################
# add_cnl_dependency
function(add_cnl_dependency target)
    ExternalProject_Get_Property(Cnl source_dir)
    target_include_directories("${target}" SYSTEM PRIVATE "${source_dir}/include")
    add_dependencies("${target}" Cnl)
endfunction(add_cnl_dependency)

# Google Test
ExternalProject_Add(
        GoogleTest
        PREFIX ${CMAKE_BINARY_DIR}/GoogleTest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "39f72ea6f5cd458860b563d7bcb7ea67546e6ea3"
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        CMAKE_ARGS -Dgtest_force_shared_crt=ON -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
)

######################################################################
# add_gtest_dependency
function(add_gtest_dependency target)
    # gtest
    ExternalProject_Get_Property(GoogleTest binary_dir)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        target_link_libraries("${target}"
                debug ${binary_dir}/lib/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${CMAKE_FIND_LIBRARY_SUFFIXES}
                debug ${binary_dir}/lib/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${CMAKE_FIND_LIBRARY_SUFFIXES}
                optimized ${binary_dir}/lib/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
                optimized ${binary_dir}/lib/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    else ()
        target_link_libraries(
                "${target}"
                general "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a"
                general "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a"
                general pthread
        )
    endif ()

    ExternalProject_Get_Property(GoogleTest source_dir)
    target_include_directories("${target}" SYSTEM PRIVATE "${source_dir}/googletest/include")

    add_dependencies("${target}" GoogleTest)
endfunction(add_gtest_dependency)

include(CTest)
add_custom_target(Tests)

foreach(source ${sample_cdsp_sources})
    string(REPLACE "\.cpp" "" stripped "${source}")
    string(REPLACE "/" "-" target "Test-${stripped}")
    add_executable(${target} ${source})
    add_test("${target}" "${target}")
    set_target_properties("${target}" PROPERTIES COMPILE_FLAGS "${COMMON_CXX_FLAGS}")

    add_gtest_dependency("${target}")
    add_cnl_dependency("${target}")

    target_include_directories(
        ${target} PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
    add_dependencies(Tests "${target}")
endforeach(source)