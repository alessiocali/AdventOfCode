set ( TargetName 2_Dive )

add_executable(
    ${TargetName}
    main.cpp

    DiveSolver.h
    DiveSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} Dive_Input.txt )
