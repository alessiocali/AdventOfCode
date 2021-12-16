set ( TargetName 6_Lanternfish )

add_executable(
    ${TargetName}
    main.cpp

    LanternfishSolver.h
    LanternfishSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} Test_Input.txt )
add_copy_input_command( ${TargetName} Lanternfish_Input.txt )
