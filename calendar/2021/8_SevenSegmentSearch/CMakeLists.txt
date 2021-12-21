set ( TargetName 8_SevenSegmentSearch )

add_executable(
    ${TargetName}
    main.cpp

    SevenSegmentSearchSolver.h
    SevenSegmentSearchSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} Test_Input.txt )
add_copy_input_command( ${TargetName} SevenSegmentSearch_Input.txt )
