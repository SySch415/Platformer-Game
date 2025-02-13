cmake_minimum_required(VERSION 3.10)
project(2DPlatformerGame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

# Include directories
include_directories(include /opt/homebrew/Cellar/sfml/2.6.1/include)
link_directories(/opt/homebrew/Cellar/sfml/2.6.1/lib)

# Add executable
add_executable(2DPlatformerGame src/main.cpp src/Player.cpp src/Obstacle.cpp)

# Explicitly set SFML include path
target_include_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/include)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} SFML::Graphics SFML::Window SFML::System)
