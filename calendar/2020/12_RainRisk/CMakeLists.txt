set ( TargetName 12_RainRisk )

add_executable(
    ${TargetName}
    main.cpp

    RainRiskSolver.h
    RainRiskSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} RainRisk_Input.txt )
