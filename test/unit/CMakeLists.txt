enable_testing()

# DSP tests
set(test_sources
        rounding.cpp
        basic_math.cpp
        biquad.cpp
        biquad_cascade.cpp
        complex.cpp
        complex_vector.cpp
        fft.cpp
        stft.cpp
        trig.cpp
        )

######################################################################
# add_cdsp_dependency
function(add_cdsp_dependencies target)
    target_link_libraries("${target}" GTest::GTest)
    target_include_directories("${target}" PRIVATE ${cnl_INCLUDE_DIRS})
    target_include_directories("${target}" PRIVATE ${GTest_INCLUDE_DIRS})
endfunction(add_cdsp_dependencies)

######################################################################
# make_test

# given the path to a source file containing gtest tests,
# creates and returns a target that runs them
function(make_test source out_target compile_flags linker_flags)

    # turn source file path into target name (e.g. "foo/bar.cpp" -> "test-unit-foo-bar")
    string(REPLACE ".cpp" "" stripped "${source}")
    string(REPLACE "/" "-" target "test-unit-${stripped}")

    # create a target and make it a test
    add_executable("${target}" "${source}")
    target_include_directories("${target}" PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
    set_target_properties("${target}" PROPERTIES COMPILE_FLAGS "${COMMON_CXX_FLAGS} ${compile_flags}")
    target_link_libraries("${target}" "${COMMON_LINK_FLAGS}" ${linker_flags})
    add_test("${target}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}")

    add_cdsp_dependencies("${target}")

    # Add to test-all custom target.
    add_dependencies(test-all "${target}")

    # Return name of test target.
    set(${out_target} "${target}" PARENT_SCOPE)
endfunction(make_test)

######################################################################
# create tests to verify CDSP

foreach(source ${test_sources})
    make_test("${source}" target "${TEST_CXX_FLAGS} ${SANITIZE_CXX_FLAGS}" "${SANITIZE_LINKER_FLAGS}")
endforeach(source)

