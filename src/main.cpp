#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include <vector>
#include <iostream>
#include <memory>

using namespace sf;
using namespace std;

// enum for game state
enum GameState {
  START,
  RUN,
  GAME_OVER
};

int main (int argc, char *argv[]) {
    
    // pop up the game window
    RenderWindow window(
        VideoMode(800, 600), "Blimp Attack");
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

    auto enemyTexture = make_shared<Texture>();
    if (!enemyTexture -> loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/images/enemysprite_updatedbounds.png")) {
      cerr << "Error loading texture" << endl;
      return -1;
    }

    // define view
    View view = window.getDefaultView();
    
    // view movement speed
    float viewSpeed = 50.0f;

    // platform positions
    vector<Obstacle> obstacles;

    // random number generator for obstacles
    srand(static_cast<unsigned>(time(nullptr)));
    
    obstacles.push_back(Obstacle(100, 100, 152, 56, enemyTexture));
    obstacles.push_back(Obstacle(700, 500, 152, 56, enemyTexture));

    // start button
    Color darkGreen(0, 100, 50);
    RectangleShape button(Vector2f(200,50));
    button.setFillColor(darkGreen);
    button.setPosition(300,275);
    
    // Game name font
    Font font;
    if (!font.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/fonts/Pixellettersfull-BnJ5.ttf")) {
      cerr << "Error loading font" << endl;
      return -1;
    }

    Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString("Start");
    startButtonText.setCharacterSize(55);
    startButtonText.setFillColor(Color::White);
    startButtonText.setPosition(
        button.getPosition().x + (button.getSize().x - startButtonText.getLocalBounds().width) / 2,
        button.getPosition().y + (button.getSize().y - startButtonText.getLocalBounds().height) / 2 - 30
    );

    Text startTitle;
    startTitle.setFont(font);
    startTitle.setString("Blimp Attack");
    startTitle.setCharacterSize(150);
    startTitle.setFillColor(Color::White);
    startTitle.setPosition(button.getPosition().x - 200, button.getPosition().y - 250);



    Clock gameClock;
    
    GameState gameState = START;

    // keep window open until user exits out
    // render spite, render obstacles, handle player updates
    while (window.isOpen()) {
      
      Event event;
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        // look for start button mouse input in start screen
        if (gameState == START && event.type == Event::MouseButtonPressed) {
          if (event.mouseButton.button == Mouse::Left) {
            Vector2i mousePosition = Mouse::getPosition(window);

            // if start button is pressed, change game state and run game
            if (button.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition))) {
              gameState = RUN;
              gameClock.restart();
            }
          }
        }
      }

      window.clear();

      if (gameState == START) {
        window.draw(button);
        window.draw(startButtonText);
        window.draw(startTitle);
      } else if (gameState == RUN) {

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
          obstacles.push_back(Obstacle(newX, newY, 152, 56, enemyTexture));
          obstacles.push_back(Obstacle(newX - 600, newY - 400, 152, 56, enemyTexture));
          lastObstacle = newX;
        }

        player.handleInput();
        player.update(deltaTime, obstacles, window, view);

        // if isGameOver, render gameover screen; else render game
        if (player.isGameOver()) {
            view.move(-offset, 0);
            gameState = GAME_OVER;
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
      } else if (gameState == GAME_OVER) {
        player.renderGameOver(window);
      }

      window.display();
    }
    return 0;
}
