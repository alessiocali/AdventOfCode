set ( TargetName 15_RambunctiousRecitation )

add_executable(
    ${TargetName}
    main.cpp

    RambunctiousRecitationSolver.h
    RambunctiousRecitationSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )