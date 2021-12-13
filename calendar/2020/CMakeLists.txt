cmake_minimum_required(VERSION 3.20)
include(../../CommonHeader.cmake)

project( AdventOfCode2020 
    DESCRIPTION
    "A set of solutions programmed in C++ for the Advent Of Code 2020"
    LANGUAGES CXX
)

include(${COMMON_ROOT_DIR}/CommonBody.cmake)

add_subdirectory(1_ReportRepair)
add_subdirectory(2_PasswordPhilosophy)
add_subdirectory(3_TobogganTrajectory)
add_subdirectory(4_PassportProcessing)
add_subdirectory(5_BinaryBoarding)
add_subdirectory(6_CustomCustoms)
add_subdirectory(7_HandyHaversacks)
add_subdirectory(8_HandheldHalting)
add_subdirectory(9_EncodingError)
add_subdirectory(10_AdapterArray)
add_subdirectory(11_SeatingSystem)
add_subdirectory(12_RainRisk)
add_subdirectory(13_ShuttleSearch)
add_subdirectory(14_DockingData)
add_subdirectory(15_RambunctiousRecitation)
add_subdirectory(16_TicketTranslation)
add_subdirectory(17_ConwayCubes)
add_subdirectory(18_OperationOrder)
add_subdirectory(19_MonsterMessages)
add_subdirectory(20_JurassicJigsaw)

add_subdirectory(tests)