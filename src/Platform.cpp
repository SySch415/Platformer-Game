#include "Platform.h"

// constuctor to initialize platforms
Platform::Platform(float x, float y, float width, float height) {
  shape.setSize(Vector2f(width, height));
  shape.setFillColor(Color::Red);
  shape.setPosition(x, y);
}

// render platform
void Platform::render(RenderWindow& window) {
  window.draw(shape);
}

// bounds of platform
FloatRect Platform::getBounds() const {
  return shape.getGlobalBounds();
}
