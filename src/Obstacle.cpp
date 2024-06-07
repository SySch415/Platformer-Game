#include "Obstacle.h"

// constuctor to initialize platforms
Obstacle::Obstacle(float x, float y, float width, float height) {
  shape.setSize(Vector2f(width, height));
  shape.setFillColor(Color::Red);
  shape.setPosition(x, y);
}

// render platform
void Obstacle::render(RenderWindow& window) {
  window.draw(shape);
}

// bounds of platform
FloatRect Obstacle::getBounds() const {
  return shape.getGlobalBounds();
}
