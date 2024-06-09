#ifndef Obstacle_H
#define Obstacle_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle {

public:

    Obstacle(float x, float y, float width, float height);
    void render(RenderWindow& window);
    FloatRect getBounds() const;

private:
    RectangleShape shape;
};

#endif 
