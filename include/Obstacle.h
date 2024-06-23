#ifndef Obstacle_H
#define Obstacle_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle {
public:

    Obstacle(float x, float y, float width, float height, const std::shared_ptr<Texture>& textureFile);
    void render(RenderWindow& window);
    FloatRect getBounds() const;

private:
    RectangleShape shape;
    std::shared_ptr<Texture> textureFile;
    FloatRect customBounds;
};

#endif 
