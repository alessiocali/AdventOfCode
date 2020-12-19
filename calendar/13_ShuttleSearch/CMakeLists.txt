set ( TargetName 13_ShuttleSearch )

add_executable(
    ${TargetName}
    main.cpp

    ShuttleSearchSolver.h
    ShuttleSearchSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} ShuttleSearch_Input.txt )
