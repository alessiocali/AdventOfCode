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
add_subdirectory(4_GiantSquid)
add_subdirectory(5_HydrothermalVenture)
add_subdirectory(6_Lanternfish)
add_subdirectory(7_TreacheryOfWhales)
add_subdirectory(8_SevenSegmentSearch)
add_subdirectory(9_SmokeBasin)
add_subdirectory(10_SyntaxScoring)
add_subdirectory(11_DumboOctopus)
add_subdirectory(12_PassagePathing)