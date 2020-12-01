set (CalendarDir ${CMAKE_SOURCE_DIR}/calendar)

add_executable(
    Tests
    catch2_main.cpp
)

target_link_libraries(
    Tests

    PRIVATE
    Catch2::Catch2
    Helpers
)

target_include_directories(
    Tests
    
    PRIVATE
)