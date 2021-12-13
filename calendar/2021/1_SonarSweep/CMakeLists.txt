set ( TargetName 1_SonarSweep )

add_executable(
    ${TargetName}
    main.cpp

    SonarSweepSolver.h
    SonarSweepSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} SonarSweep_Input.txt )
