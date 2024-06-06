#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

int main (int argc, char *argv[]) {
    
    // pop up the game window
    RenderWindow window(
        VideoMode(800, 600), "2D Platformer Game");
    Player player;

    // platform positions
    vector<Platform> platforms;
    platforms.push_back(Platform(100, 100, 20, 200));
    
    platforms.push_back(Platform(700, 500, 20, 200));

    Clock gameClock;
    
    // keep window open until user exits out
    // render spite, render platforms, handle player updates
    while (window.isOpen()) {
      
      Event event;
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
      }

      float deltaTime = gameClock.restart().asSeconds();
      
      player.handleInput();
      player.update(deltaTime, platforms, window);

      window.clear();

      if (player.isGameOver()) {
          player.renderGameOver(window);
      } else {

        player.render(window);

        for (auto& platform : platforms) {
          platform.render(window);
        }

      }
      window.display();
    }

    return 0;
}
