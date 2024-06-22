#include "Obstacle.h"
#include <iostream>

using namespace sf;
using namespace std;


// constuctor to initialize platforms
Obstacle::Obstacle(float x, float y, float width, float height, const shared_ptr<Texture>& textureFile) {
  shape.setSize(Vector2f(width, height));
  
  if (textureFile) {
    this->textureFile = textureFile;
    shape.setTexture(textureFile.get());
  } else {
    cerr << "Image is null" << endl;
  }
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
