#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Platform {

public:

    Platform(float x, float y, float width, float height);
    void render(RenderWindow& window);
    FloatRect getBounds() const;

private:
    RectangleShape shape;
};

#endif 
