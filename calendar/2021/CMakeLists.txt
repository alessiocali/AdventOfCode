cmake_minimum_required(VERSION 3.20)
include(../../CommonHeader.cmake)

project( AdventOfCode2021
    DESCRIPTION
    "A set of solutions programmed in C++ for the Advent Of Code 2021"
    LANGUAGES CXX
)

include(${COMMON_ROOT_DIR}/CommonBody.cmake)

add_subdirectory(1_SonarSweep)
add_subdirectory(2_Dive)
add_subdirectory(3_BinaryDiagnostic)