#include "UtilSFML.h"

bool CursorOnSprite(sf::RenderWindow &window, sf::Sprite &sprite){
  sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  return sprite.getGlobalBounds().contains(mousePosition);
}
