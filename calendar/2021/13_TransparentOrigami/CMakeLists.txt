set ( TargetName 13_TransparentOrigami )

add_executable(
    ${TargetName}
    main.cpp

    TransparentOrigamiSolver.h
    TransparentOrigamiSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} TransparentOrigami_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )