set (CalendarDir ${CMAKE_SOURCE_DIR})

add_executable(
    Tests
    catch2_main.cpp

    ${CalendarDir}/1_ReportRepair/ReportRepairSolver.h
    ${CalendarDir}/1_ReportRepair/ReportRepairSolver.cpp

    ${CalendarDir}/2_PasswordPhilosophy/PasswordPhilosophySolver.h
    ${CalendarDir}/2_PasswordPhilosophy/PasswordPhilosophySolver.cpp

    ${CalendarDir}/3_TobogganTrajectory/TobogganTrajectorySolver.h
    ${CalendarDir}/3_TobogganTrajectory/TobogganTrajectorySolver.cpp

    ${CalendarDir}/4_PassportProcessing/PassportProcessingSolver.h
    ${CalendarDir}/4_PassportProcessing/PassportProcessingSolver.cpp

    ${CalendarDir}/5_BinaryBoarding/BinaryBoardingSolver.h
    ${CalendarDir}/5_BinaryBoarding/BinaryBoardingSolver.cpp

    ${CalendarDir}/6_CustomCustoms/CustomCustomsSolver.h
    ${CalendarDir}/6_CustomCustoms/CustomCustomsSolver.cpp

    ${CalendarDir}/7_HandyHaversacks/HandyHaversacksSolver.h
    ${CalendarDir}/7_HandyHaversacks/HandyHaversacksSolver.cpp

    ${CalendarDir}/8_HandheldHalting/HandheldHaltingSolver.h
    ${CalendarDir}/8_HandheldHalting/HandheldHaltingSolver.cpp

    ${CalendarDir}/9_EncodingError/EncodingErrorSolver.h
    ${CalendarDir}/9_EncodingError/EncodingErrorSolver.cpp

    ${CalendarDir}/10_AdapterArray/AdapterArraySolver.h
    ${CalendarDir}/10_AdapterArray/AdapterArraySolver.cpp

    ${CalendarDir}/11_SeatingSystem/SeatingSystemSolver.h
    ${CalendarDir}/11_SeatingSystem/SeatingSystemSolver.cpp
)

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(
    Tests

    PRIVATE
    Catch2::Catch2
    Helpers
)

target_include_directories(
    Tests
    
    PRIVATE
    ${CalendarDir}/1_ReportRepair
    ${CalendarDir}/2_PasswordPhilosophy
    ${CalendarDir}/3_TobogganTrajectory
    ${CalendarDir}/4_PassportProcessing
    ${CalendarDir}/5_BinaryBoarding
    ${CalendarDir}/6_CustomCustoms
    ${CalendarDir}/7_HandyHaversacks
    ${CalendarDir}/8_HandheldHalting
    ${CalendarDir}/9_EncodingError
    ${CalendarDir}/10_AdapterArray
    ${CalendarDir}/11_SeatingSystem
)

file ( COPY ${CalendarDir}/1_ReportRepair/ReportRepair_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/2_PasswordPhilosophy/PasswordPhilosophy_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/3_TobogganTrajectory/TobogganTrajectory_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/4_PassportProcessing/PassportProcessing_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/5_BinaryBoarding/BinaryBoarding_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/6_CustomCustoms/CustomCustoms_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/7_HandyHaversacks/HandyHaversacks_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/8_HandheldHalting/HandheldHalting_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/9_EncodingError/EncodingError_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/10_AdapterArray/AdapterArray_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )
file ( COPY ${CalendarDir}/11_SeatingSystem/SeatingSystem_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )