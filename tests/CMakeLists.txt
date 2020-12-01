set (CalendarDir ${CMAKE_SOURCE_DIR}/calendar)

add_executable(
    Tests
    catch2_main.cpp

    ${CalendarDir}/1_ReportRepair/ReportRepairSolver.h
    ${CalendarDir}/1_ReportRepair/ReportRepairSolver.cpp
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
)

file ( COPY ${CalendarDir}/1_ReportRepair/ReportRepair_Input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/ )