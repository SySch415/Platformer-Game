#include "Player.h"
#include "Platform.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

// Define Player methods
Player::Player() : speed(200.0f), jumpHeight(300.0f), gravity(980.0f), isJumping(false) {
    // load a texture image
    if (!texture.loadFromFile("/Users/sy/dev/cpp-projects/2d_platformer_game/assets/images/resized_sprite.png")) {
        
      cout << "Error loading image" << endl; //TODO: change error throw
    }
    sprite.setTexture(texture);
    sprite.setPosition(400,300); // start position
    velocity = Vector2f(0,0);
}

void Player::handleInput() {

    // player moves left
    if (Keyboard::isKeyPressed(Keyboard::Left) && !isJumping) {
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
    if (Keyboard::isKeyPressed(Keyboard::Up) && !isJumping || 
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

void Player::update(float deltaTime, const std::vector<Platform>& platforms, const RenderWindow& window) {

    // player jumps calculated with time and gravity
    velocity.y += gravity * deltaTime;
    // player moves calculated with time
    sprite.move(velocity * deltaTime);

    // Wrap sprite around screen if leaving bounds
    FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.left + bounds.width < 0) {
      sprite.setPosition(window.getSize().x, sprite.getPosition().y);

    } else if (bounds.left > window.getSize().x) {
      sprite.setPosition(-bounds.width, sprite.getPosition().y);
    }
    
    // if sprite dies, reset position to start position
    if (bounds.top > window.getSize().y) {
      sprite.setPosition(400,300);
    }

    // for sprite collisions against platform
    for (const auto& platform : platforms) {

      if (sprite.getGlobalBounds().intersects(platform.getBounds()) && velocity.y > 0) {
        velocity.y = 0;
        isJumping = false;
        sprite.setPosition(sprite.getPosition().x, platform.getBounds().top - sprite.getGlobalBounds().height);
      }
    }

    if (velocity != Vector2f(0,0)) {
      isJumping = true;
    }
}

void Player::render(RenderWindow& window) {
    // Render player
    window.draw(sprite);
}
