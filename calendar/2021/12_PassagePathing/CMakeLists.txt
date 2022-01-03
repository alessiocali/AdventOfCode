set ( TargetName 12_PassagePathing )

add_executable(
    ${TargetName}
    main.cpp

    PassagePathingSolver.h
    PassagePathingSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} PassagePathing_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )
add_copy_input_command( ${TargetName} Test_Input2.txt )