set ( TargetName 11_DumboOctopus )

add_executable(
    ${TargetName}
    main.cpp

    DumboOctopusSolver.h
    DumboOctopusSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} DumboOctopus_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )