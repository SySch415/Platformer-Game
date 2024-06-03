cmake_minimum_required(VERSION 3.10)
project(2DPlatformerGame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Include directories
include_directories(include /opt/homebrew/Cellar/sfml/2.6.1/include)
link_directories(/opt/homebrew/Cellar/sfml/2.6.1/lib)

# Add executable
add_executable(2DPlatformerGame src/main.cpp src/Player.cpp src/Platform.cpp)

# Link SFML libraries
target_link_libraries(2DPlatformerGame sfml-system sfml-window sfml-graphics)
