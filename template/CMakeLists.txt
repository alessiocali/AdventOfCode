set ( TargetName ||DAY_TARGET_NAME|| )

add_executable(
    ${TargetName}
    main.cpp

    ||PROBLEM_SOLVER||.h
    ||PROBLEM_SOLVER||.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} ||DAY_TARGET_INPUT|| )
