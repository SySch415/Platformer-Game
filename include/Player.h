#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obstacle.h"

using namespace sf;

class Player {
public:
    Player();
    void handleInput();
    void update(float deltaTime, const std::vector<Obstacle>& obstacles, const RenderWindow& window);
    void render(RenderWindow& window);
    bool isGameOver() const;
    void renderGameOver(RenderWindow& window);

private:
    Texture texture;
    Sprite sprite;
    float speed;
    float jumpHeight;
    float gravity;
    bool isJumping;
    Vector2f velocity;

    Text gameOverText;
    Font font;
    bool gameOver;
};

#endif // PLAYER_H
