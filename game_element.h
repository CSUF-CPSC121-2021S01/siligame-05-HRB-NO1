#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <vector>
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() {
    x_ = 0;
    y_ = 0;
    width_ = 50;
    height_ = 50;
  }

  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  int GetX() { return x_; }
  int GetY() { return y_; }

  int GetWidth() { return width_; }

  int GetHeight() { return height_; }

  virtual void Draw(graphics::Image &screen) = 0;

  void SetIsActive(bool is_active) { is_active_ = is_active; }

  int GetIsActive() { return is_active_; }

  virtual void Move(const graphics::Image &screen) = 0;

  bool IntersectsWith(GameElement *gameElement);

  bool IsOutOfBounds(const graphics::Image &screen);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif
