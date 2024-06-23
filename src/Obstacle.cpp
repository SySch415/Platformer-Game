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
    shape.setTextureRect(IntRect(0, 0, textureFile->getSize().x, textureFile->getSize().y));

  } else {
    cerr << "Image is null" << endl;
  }

  shape.setPosition(x, y);

  // change bounds of obstacle to better fit collision with texture
  customBounds = FloatRect(x + 30, y + 30, width - 50, height - 50);
}

// render platform
void Obstacle::render(RenderWindow& window) {
  window.draw(shape);
}

// bounds of platform
FloatRect Obstacle::getBounds() const {
  return customBounds;
}
