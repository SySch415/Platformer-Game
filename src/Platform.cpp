#include "Platform.h"

Platform::Platform(float x, float y, float width, float height) {
  shape.setSize(Vector2f(width, height));
  shape.setFillColor(Color::Green);
  shape.setPosition(x, y);
}

void Platform::render(RenderWindow& window) {
  window.draw(shape);
}

FloatRect Platform::getBounds() const {
  return shape.getGlobalBounds();
}
