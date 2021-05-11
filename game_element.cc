#include "game_element.h"
bool GameElement::IntersectsWith(GameElement *gameElement) {
  return !(GetX() > gameElement->GetX() + gameElement->GetWidth() ||
           gameElement->GetX() > x_ + GetWidth() ||
           GetY() > gameElement->GetY() + gameElement->GetHeight() ||
           gameElement->GetY() > y_ + GetHeight());
}
/*
bool GameElement::IntersectsWith(GameElement &gameElement) {
  return !(GetX() > gameElement.GetX() + gameElement.GetWidth() ||
           gameElement.GetX() > x_ + GetWidth() ||
           GetY() > gameElement.GetY() + gameElement.GetHeight() ||
           gameElement.GetY() > y_ + GetHeight());
}
*/
bool GameElement::IsOutOfBounds(const graphics::Image &screen) {
  if (GetX() + GetWidth() > screen.GetWidth() ||
      GetY() + GetHeight() > screen.GetHeight() || GetX() < 1 || GetY() < 1) {
    return true;
  } else {
    return false;
  }
}
