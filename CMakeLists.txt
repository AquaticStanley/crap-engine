find_package(SFML 2.5 COMPONENTS system window graphics network audio main REQUIRED)
add_executable(myapp)
target_link_libraries(myapp sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)