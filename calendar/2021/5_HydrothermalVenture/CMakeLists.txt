set ( TargetName 5_HydrothermalVenture )

add_executable(
    ${TargetName}
    main.cpp

    HydrothermalVentureSolver.h
    HydrothermalVentureSolver.cpp
)

target_include_directories( ${TargetName} PRIVATE / )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} Test_Input.txt )
add_copy_input_command( ${TargetName} HydrothermalVenture_Input.txt )
