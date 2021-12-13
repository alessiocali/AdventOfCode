set ( TargetName 7_HandyHaversacks )

add_executable(
    ${TargetName}
    main.cpp

    HandyHaversacksSolver.h
    HandyHaversacksSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} HandyHaversacks_Input.txt )
