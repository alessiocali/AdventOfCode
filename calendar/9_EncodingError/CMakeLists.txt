set ( TargetName 9_EncodingError )

add_executable(
    ${TargetName}
    main.cpp

    EncodingErrorSolver.h
    EncodingErrorSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} EncodingError_Input.txt )
