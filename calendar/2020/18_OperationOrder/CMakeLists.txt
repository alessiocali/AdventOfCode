set ( TargetName 18_OperationOrder )

add_executable(
    ${TargetName}
    main.cpp

    OperationOrderSolver.h
    OperationOrderSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} OperationOrder_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )
