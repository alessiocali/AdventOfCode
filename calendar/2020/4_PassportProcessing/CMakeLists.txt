set ( TargetName 4_PassportProcessing )

add_executable(
    ${TargetName}
    main.cpp

    PassportProcessingSolver.h
    PassportProcessingSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} PassportProcessing_Input.txt )
