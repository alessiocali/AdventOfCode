set ( TargetName 11_SeatingSystem )

add_executable(
    ${TargetName}
    main.cpp

    SeatingSystemSolver.h
    SeatingSystemSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} SeatingSystem_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )
