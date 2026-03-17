cmake_minimum_required(VERSION 3.10)
project(2DPlatformerGame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 3 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(2DPlatformerGame src/main.cpp src/Player.cpp src/Obstacle.cpp)

# Explicitly set SFML include path
target_include_directories(2DPlatformerGame PRIVATE /opt/homebrew/include)

# Link SFML libraries
target_link_libraries(2DPlatformerGame sfml-graphics sfml-window sfml-system)
