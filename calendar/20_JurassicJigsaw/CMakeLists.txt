set ( TargetName 20_JurassicJigsaw )

add_executable(
    ${TargetName}
    src/main.cpp

    src/Image.h
    src/Image.cpp

    src/ImageMatcher.h
    src/ImageMatcher.cpp

    src/JurassicJigsaw.h
    src/JurassicJigsaw.cpp

    src/Parser.h
    src/Parser.cpp

    src/PatternSearcher.h
    src/PatternSearcher.cpp

    src/Problem.h
    src/Problem.cpp

    src/Solver.h
    src/Solver.cpp

    src/Tile.h
    src/Tile.cpp
)

target_include_directories( ${TargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
target_link_libraries( ${TargetName} PRIVATE Helpers )

add_copy_input_command( ${TargetName} JurassicJigsaw_Input.txt )
add_copy_input_command( ${TargetName} Test_Input.txt )
