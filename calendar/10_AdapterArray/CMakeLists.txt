set ( TargetName 10_AdapterArray )

add_executable(
    ${TargetName}
    main.cpp

    AdapterArraySolver.h
    AdapterArraySolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} AdapterArray_Input.txt )
