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

    Texture backgroundTexture;

    // load background image
    if (!backgroundTexture.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/images/6fb59f66648033799c3059fd1943b319.png")) {
      cerr << "Error loading background image" << endl;
      return -1;
    }

    // background sprites for scrolling
    Sprite backgroundSprite, backgroundSprite2;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    // size of background image and game window 
    Vector2u textureSize = backgroundTexture.getSize();
    Vector2u windowSize = window.getSize();

    // scale background to size of window
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite2.setScale(scaleX, scaleY);

    // position second background image to the right of first for scrolling
    backgroundSprite2.setPosition(backgroundSprite.getGlobalBounds().width, 0);

    // define view
    View view = window.getDefaultView();
    
    // view movement speed
    float viewSpeed = 50.0f;

    // platform positions
    vector<Obstacle> obstacles;

    // random number generator for obstacles
    srand(static_cast<unsigned>(time(nullptr)));
    
    obstacles.push_back(Obstacle(100, 100, 20, 200));
    obstacles.push_back(Obstacle(700, 500, 20, 200));

    // start button
    RectangleShape button(Vector2f(200,50));
    button.setFillColor(Color::Blue);
    button.setPosition(300,275);

    Clock gameClock;
    
    // keep window open until user exits out
    // render spite, render obstacles, handle player updates
    while (window.isOpen()) {
      
      Event event;
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
      }

      // game time and view scrolling offset
      float deltaTime = gameClock.restart().asSeconds();
      float offset = viewSpeed * deltaTime;
      
      // move view to the right 
      view.move(offset, 0);

      // get width of background image
      float backgroundWidth = backgroundSprite.getGlobalBounds().width;

      // move background image at opposite direction of view
      backgroundSprite.move(-offset, 0);
      backgroundSprite2.move(-offset, 0);
      
      // position sprites to the right of previous sprite as sprite leaves view
      if (backgroundSprite.getPosition().x + backgroundWidth < window.getView().getCenter().x - window.getView().getSize().x / 2) {
        backgroundSprite.setPosition(backgroundSprite2.getPosition().x + backgroundWidth, 0);
      }
      if (backgroundSprite2.getPosition().x + backgroundWidth < window.getView().getCenter().x - window.getView().getSize().x / 2) {
        backgroundSprite2.setPosition(backgroundSprite.getPosition().x + backgroundWidth, 0);
      }

      // render new obstacles as view changes
      static float lastObstacle = view.getCenter().x + 400;
      if (view.getCenter().x + 400 > lastObstacle) {
        float newX = lastObstacle + 200;
        float newY = static_cast<float>(rand() % 300);
        obstacles.push_back(Obstacle(newX, newY, 20, 200));
        obstacles.push_back(Obstacle(newX - 600, newY - 400, 20, 200));
        lastObstacle = newX;
      }

      player.handleInput();
      player.update(deltaTime, obstacles, window, view);

      window.clear();

      // if isGameOver, render gameover screen; else render game
      if (player.isGameOver()) {
          view.move(-offset,0); // fixes gameover text moving
          player.renderGameOver(window);
      } else {

        window.draw(backgroundSprite);
        window.draw(backgroundSprite2);

        player.render(window);
        
        window.setView(view);

        // render obstacles
        for (auto& obstacle : obstacles) {
          obstacle.render(window);
        }
      }
      window.display();
    }
    return 0;
}
