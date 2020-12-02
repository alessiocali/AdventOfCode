set ( TargetName 2_PasswordPhilosophy )

add_executable(
    ${TargetName}
    main.cpp

    PasswordPhilosophySolver.h
    PasswordPhilosophySolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} PasswordPhilosophy_Input.txt )
