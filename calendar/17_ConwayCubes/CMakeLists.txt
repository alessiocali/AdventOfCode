set ( TargetName 17_ConwayCubes )

add_executable(
    ${TargetName}
    main.cpp

    ConwayCubesSolver.h
    ConwayCubesSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} ConwayCubes_Input.txt )
