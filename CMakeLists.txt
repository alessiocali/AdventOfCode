cmake_minimum_required(VERSION 3.14)

set(
    CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

project( AdventOfCode2020 
    DESCRIPTION
    "A set of solutions programmed in C++ for the Advent Of Code 2020"
    LANGUAGES CXX
)

macro (add_copy_input_command TargetName InputFile)
    add_custom_command(
        TARGET ${TargetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/calendar/${TargetName}/${InputFile}
        ${CMAKE_CURRENT_BINARY_DIR}/${InputFile}
    )
endmacro()

# set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Only build static libs.")

# Add helper classes
add_subdirectory(helpers)

# Add anti regression tests
add_subdirectory(tests)

# Executables for each day
add_subdirectory(calendar/1_ReportRepair)