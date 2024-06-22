#include "Player.h"
#include "Obstacle.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

// Define Player methods
Player::Player() : speed(200.0f), jumpHeight(300.0f), gravity(980.0f), isJumping(false), gameOver(false) {
    
    // load a texture image
    if (!texture.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/images/blimp_transparent copy.png")) {
        
      cerr << "Error loading image" << endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(400,300); // start position
    velocity = Vector2f(0,0);

    // load angled sprite texture for up key input
    if (!upTexture.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/images/blimp_transparent copy 2.png")) {
      cerr << "Error loading image" << endl;
    }
    
    // load font
    if (!font.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/fonts/Tiny5-Regular.ttf")) {
      cerr << "Error loading font" << endl;
      return;
    }

    // set up "game over" text
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::White);
}

void Player::handleInput() {

    // player moves left
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      velocity.x = -speed;   
    }
    
    // sprite stops when depressing left key
    if (!(Keyboard::isKeyPressed(Keyboard::Left))) {
      velocity.x = 0;
    }

    // player moves right
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      velocity.x = speed;
    }
    
    // player moves up
    if (Keyboard::isKeyPressed(Keyboard::Up) || 
        Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left) ||
        Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right)) {

        velocity.y = -jumpHeight;
        isJumping = true;
        sprite.setTexture(upTexture);
        sprite.setTextureRect(IntRect(0, 0, upTexture.getSize().x, upTexture.getSize().y));
    }

    // update texture if player stops moving up
    if (!(Keyboard::isKeyPressed(Keyboard::Up))) {
      sprite.setTexture(texture);
    }
}

void Player::update(float deltaTime, const std::vector<Obstacle>& obstacles, const RenderWindow& window, const View& view) {

    bool isGameOver = false;

    // player jumps calculated with time and gravity
    velocity.y += gravity * deltaTime;
    // player moves calculated with time
    sprite.move(velocity * deltaTime);

    // bounds of sprite
    FloatRect bounds = sprite.getGlobalBounds();

    // for sprite collisions against platform
    isGameOver = false;
    
    // if sprite leaves lower bound -> game over
    if (bounds.top > window.getSize().y) {
      gameOver = true;
      gameOverText.setPosition(view.getCenter().x - gameOverText.getGlobalBounds().width / 2,
          view.getCenter().y - gameOverText.getGlobalBounds().height / 2);
    }

    // obstacle rendering
    // check if playter touches obstacles; initiate game over state
    for (const auto& obstacle : obstacles) {

      if (sprite.getGlobalBounds().intersects(obstacle.getBounds())) {
        gameOver = true;
        gameOverText.setPosition(view.getCenter().x - gameOverText.getGlobalBounds().width / 2,
            view.getCenter().y - gameOverText.getGlobalBounds().height / 2);
        break;
      }
    }
}

// player rendering
void Player::render(RenderWindow& window) {
    window.draw(sprite);
}

// returns true if sprite collides with obstacle
bool Player::isGameOver() const {
  return gameOver;
}

// if player collides with obstacle, render game over screen
void Player::renderGameOver(RenderWindow& window) {
    window.draw(gameOverText);
}
