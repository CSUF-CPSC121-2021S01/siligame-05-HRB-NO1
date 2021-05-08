#include "opponent.h"
#include <vector>
#include "cpputils/graphics/image.h"

void OpponentProjectile::Draw(graphics::Image &screen) {
  screen.DrawRectangle(x_, y_, 2, 2, kOrange);
  screen.DrawRectangle(x_ + 3, y_, 2, 2, kOrange);
  screen.DrawRectangle(x_ + 3, x_ + 3, 2, 2, kOrange);
  screen.DrawRectangle(x_, y_ + 3, 2, 2, kOrange);
}

void OpponentProjectile::PadPoints(std::vector<int> &points, int pad_x,
                                   int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}

void Opponent::Draw(graphics::Image &screen) {
  std::vector<int> layer1 = {12, 1,  33, 6,  40, 21, 47, 8, 45, 35, 37, 48,
                             9,  48, 2,  39, 3,  19, 10, 5, 10, 12, 23, 19};
  PadPoints(layer1, x_, y_);
  screen.DrawPolygon(layer1, kRed);

  std::vector<int> layer2 = {20, 7,  31, 11, 39, 24, 43, 22, 42, 33, 36,
                             46, 12, 46, 6,  38, 8,  14, 15, 21, 28, 22};
  PadPoints(layer2, x_, y_);
  screen.DrawPolygon(layer2, kOrange);

  std::vector<int> layer3 = {32, 21, 38, 27, 38, 33, 33, 42, 15,
                             42, 10, 37, 10, 21, 15, 24, 32, 25};
  PadPoints(layer3, x_, y_);
  screen.DrawPolygon(layer3, kYellow);
}

void Opponent::PadPoints(std::vector<int> &points, int pad_x, int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}

void Opponent::Move(const graphics::Image &screen) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

void OpponentProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() + 1);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
