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
    cxx_std_17
)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
find_package(Boost REQUIRED COMPONENTS program_options)

target_link_libraries( Helpers 
    PUBLIC 
    sfml-system 
    sfml-window 
    sfml-graphics 
    
    Boost::boost

    PRIVATE
    Boost::program_options
)