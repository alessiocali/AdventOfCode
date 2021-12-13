set ( TargetName 14_DockingData )

add_executable(
    ${TargetName}
    main.cpp

    DockingDataSolver.h
    DockingDataSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} DockingData_Input.txt )
