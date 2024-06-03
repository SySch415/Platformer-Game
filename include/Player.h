#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platform.h"

using namespace sf;

class Player {
public:
    Player();
    void handleInput();
    void update(float deltaTime, const std::vector<Platform>& platforms, const RenderWindow& window);
    void render(RenderWindow& window);

private:
    Texture texture;
    Sprite sprite;
    float speed;
    float jumpHeight;
    float gravity;
    bool isJumping;
    Vector2f velocity;
};

#endif // PLAYER_H
