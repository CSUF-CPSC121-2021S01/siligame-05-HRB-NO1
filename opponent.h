#ifndef OPPONENT_H
#define OPPONENT_H

#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}

  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image &screen);

  void Move(const graphics::Image &screen);
// new add

 private:

  void PadPoints(std::vector<int> &points, int pad_x, int pad_y);

  const graphics::Color kOrange{255, 165, 0};
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}

  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &screen);

  std::unique_ptr<OpponentProjectile> LaunchProjectile() {
    std::unique_ptr<OpponentProjectile> OpponentProjectileFactory = std::make_unique<OpponentProjectile>(GetX(), GetY());
    counter++;
    if (counter < 10) {
      return nullptr;// std::move
    } else {
      return std::move(OpponentProjectileFactory);
    }
  }

  void Move(const graphics::Image &screen);

 private:
  int counter = 0;

  void PadPoints(std::vector<int> &points, int pad_x, int pad_y);

  const graphics::Color kRed{255, 0, 0};
  const graphics::Color kOrange{255, 165, 0};
  const graphics::Color kYellow{255, 255, 0};
};

#endif
