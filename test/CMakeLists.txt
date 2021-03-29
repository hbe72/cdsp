include(cmake/common.cmake)

include(ExternalProject)

add_custom_target(test-all)

find_package(GTest)
if (${GTest_FOUND})
    message(STATUS "GTest found")
    add_subdirectory(unit)
else ()
    message(STATUS "Google Test is required to build unit tests.")
endif ()