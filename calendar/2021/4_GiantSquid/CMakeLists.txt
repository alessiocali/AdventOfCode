set ( TargetName 4_GiantSquid )

add_executable(
    ${TargetName}
    main.cpp

    GiantSquidSolver.h
    GiantSquidSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} Test_Input.txt )
add_copy_input_command( ${TargetName} GiantSquid_Input.txt )
