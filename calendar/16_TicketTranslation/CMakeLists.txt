set ( TargetName 16_TicketTranslation )

add_executable(
    ${TargetName}
    main.cpp

    TicketTranslationSolver.h
    TicketTranslationSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} TicketTranslation_Input.txt )
