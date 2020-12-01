set ( TargetName 1_ReportRepair )

add_executable(
    ${TargetName}
    main.cpp

    ReportRepairSolver.h
    ReportRepairSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} ReportRepair_Input.txt )
