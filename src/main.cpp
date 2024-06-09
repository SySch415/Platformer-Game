#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

int main (int argc, char *argv[]) {
    
    // pop up the game window
    RenderWindow window(
        VideoMode(800, 600), "2D Platformer Game");
    Player player;

    // define view
    View view(FloatRect(0, 0, 800, 600));
    
    float viewSpeed = 50.0f;

    // platform positions
    vector<Obstacle> obstacles;

    // random number generator for obstacles
    srand(static_cast<unsigned>(time(nullptr)));
    
    obstacles.push_back(Obstacle(100, 100, 20, 200));
    obstacles.push_back(Obstacle(700, 500, 20, 200));

    Clock gameClock;
    
    // keep window open until user exits out
    // render spite, render obstacles, handle player updates
    while (window.isOpen()) {
      
      Event event;
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
      }

      float deltaTime = gameClock.restart().asSeconds();
      
      view.move(viewSpeed * deltaTime, 0);

      static float lastObstacle = view.getCenter().x + 400;
      if (view.getCenter().x + 400 > lastObstacle) {
        float newX = lastObstacle + 200;
        float newY = static_cast<float>(rand() % 600);
        obstacles.push_back(Obstacle(newX, newY, 20, 200));
        obstacles.push_back(Obstacle(newX - 600, newY - 400, 20, 200));
        lastObstacle = newX;
      }

      player.handleInput();
      player.update(deltaTime, obstacles, window, view);

      window.clear();

      if (player.isGameOver()) {

          player.renderGameOver(window);
      } else {

        player.render(window);
        
         window.setView(view);

        for (auto& obstacle : obstacles) {
          obstacle.render(window);
        }

      }
      window.display();
    }

    return 0;
}
