add_library( Helpers
    include/CommonDefines.h
    include/MathHelpers.h
    include/ProblemSolver.h

    include/SimpleControllableView.h
    src/SimpleControllableView.cpp

    include/CommonHelpers.h
    src/CommonHelpers.cpp
)

target_include_directories( Helpers
    PUBLIC    
    include/
)

target_compile_features( Helpers
    PUBLIC
    cxx_std_20
)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(range-v3 CONFIG REQUIRED)

target_link_libraries( Helpers 
    PUBLIC 
    sfml-system 
    sfml-window 
    sfml-graphics 
    
    Boost::boost

    range-v3
    range-v3-concepts

    PRIVATE
    Boost::program_options
)