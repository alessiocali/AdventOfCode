set ( TargetName 3_TobogganTrajectory )

add_executable(
    ${TargetName}
    main.cpp

    TobogganTrajectorySolver.h
    TobogganTrajectorySolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} TobogganTrajectory_Input.txt )
