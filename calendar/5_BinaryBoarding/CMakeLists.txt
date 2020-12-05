set ( TargetName 5_BinaryBoarding )

add_executable(
    ${TargetName}
    main.cpp

    BinaryBoardingSolver.h
    BinaryBoardingSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} BinaryBoarding_Input.txt )
