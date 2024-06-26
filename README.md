# 2D Platformer Game

A very simple(so far) 2d platform game built using C++ and SFML

-------------------------------
Name: Simon "Sy" Schmidt

Language: C++

## Features

- Player flying movement
- jumping
- seamless view movement
- Platform collisions

NOTE: Many more features to be added
    
    - Game levels
    - improved obstacles/platforms
    - Enemy sprites
    - weapons

## Dependencies

This project depends on the SFML library. You need to have SFML installed to build and run the game

## Installation

1. Clone the repository

  git clone https://github.com/SySch415/Platformer-Game.github
  
  cd Platformer-Game

2. Install SFML

  Follow the instructions on the SFML site: https://www.sfml-dev.org/download.php to install

  For macos, you can use Homebrew:
  
    brew install sfml

  For Linux, use your distros package manager:

  For Ubuntu/Debian use apt:

    sudo apt-get install libsfml-dev

  For Arch Linux:

    sudo pacman -S sfml

## Building the project

1. Navigate to project directory
  
    cd Platformer-Game

2. Create a build dir and navigate to it 

    mkdir build
    cd build

3. Generate build files with CMake

    cmake

4. Build the project

    make

## Running the Game

1. After building, run the executable

    ./Platformer-Game


## Usage

- Use the arrow keys to keep player flying; like flappy bird.
- The player will die when hitting obstacles, falling out of bounds
- Game currently does not end.
    


