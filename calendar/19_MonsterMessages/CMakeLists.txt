set ( TargetName 19_MonsterMessages )

add_executable(
    ${TargetName}
    main.cpp

    MonsterMessagesSolver.h
    MonsterMessagesSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} MonsterMessages_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )