set ( TargetName 6_CustomCustoms )

add_executable(
    ${TargetName}
    main.cpp

    CustomCustomsSolver.h
    CustomCustomsSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} CustomCustoms_Input.txt )
