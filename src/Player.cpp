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
    /*
    // sprite stops when depressing right key
    if (!(Keyboard::isKeyPressed(Keyboard::Right))) {
      velocity.x = 0 ;
    }
    */
    // player moves right
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      velocity.x = speed;
    }
    // player jumps
    if (Keyboard::isKeyPressed(Keyboard::Up) || 
        Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left) ||
        Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right)) {

      velocity.y = -jumpHeight;
      isJumping = true;
    }
    

    /*
    // player moves Down
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
      sprite.move(0, speed * 0.1f);
    }
    */
}

void Player::update(float deltaTime, const std::vector<Obstacle>& obstacles, const RenderWindow& window, const View& view) {

    bool isGameOver = false;

    // player jumps calculated with time and gravity
    velocity.y += gravity * deltaTime;
    // player moves calculated with time
    sprite.move(velocity * deltaTime);

    
    FloatRect bounds = sprite.getGlobalBounds();

    /*
    
    // Wrap sprite around screen if leaving bounds
    if (bounds.left + bounds.width < 0) {
      sprite.setPosition(window.getSize().x, sprite.getPosition().y);

    } else if (bounds.left > window.getSize().x) {
      sprite.setPosition(-bounds.width, sprite.getPosition().y);
    }
    */
    
    // if sprite dies, reset position to start position
    if (bounds.top > window.getSize().y) {
      sprite.setPosition(400,300);
    }

    // for sprite collisions against platform
    isGameOver = false;
    for (const auto& obstacle : obstacles) {

      if (sprite.getGlobalBounds().intersects(obstacle.getBounds())) {
        gameOver = true;
        gameOverText.setPosition(view.getCenter().x - gameOverText.getGlobalBounds().width / 2,
            view.getCenter().y - gameOverText.getGlobalBounds().height / 2);
        break;
      }
    }
}

void Player::render(RenderWindow& window) {
    // Render player
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
