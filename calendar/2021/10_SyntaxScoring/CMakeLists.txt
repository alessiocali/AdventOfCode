set ( TargetName 10_SyntaxScoring )

add_executable(
    ${TargetName}
    main.cpp

    SyntaxScoringSolver.h
    SyntaxScoringSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} SyntaxScoring_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )