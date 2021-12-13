set ( TargetName 8_HandheldHalting )

add_executable(
    ${TargetName}
    main.cpp

    HandheldHaltingSolver.h
    HandheldHaltingSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} HandheldHalting_Input.txt )
