#include "player.h"
#include <vector>
#include "cpputils/graphics/image.h"

void PlayerProjectile::Draw(graphics::Image &screen) {
  screen.DrawRectangle(x_ + 1, y_, 2, 2, kBlue);
  screen.DrawRectangle(x_, y_ + 3, 2, 2, kBlue);
  screen.DrawRectangle(x_ + 3, y_ + 3, 2, 2, kBlue);
}

void PlayerProjectile::PadPoints(std::vector<int> &points, int pad_x,
                                 int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}

void Player::Draw(graphics::Image &screen) {
  screen.DrawLine(x_ + 19, y_, x_ + 30, y_, kBlack);
  screen.DrawRectangle(x_ + 24, y_ + 1, 2, 2, kBlack);
  std::vector<int> engine = {20, 3, 29, 3, 31, 8, 18, 8};
  PadPoints(engine, x_, y_);
  screen.DrawPolygon(engine, kGreen);
  std::vector<int> wing = {44, 14, 49, 20, 49, 27, 43, 27, 43, 29,
                           37, 29, 37, 27, 12, 27, 12, 29, 6,  29,
                           6,  27, 0,  27, 0,  20, 5,  14};
  PadPoints(wing, x_, y_);
  screen.DrawPolygon(wing, kRed);
  std::vector<int> body = {17, 9, 32, 9, 27, 40, 22, 40};
  PadPoints(body, x_, y_);
  screen.DrawPolygon(body, kBlue);
  std::vector<int> tail = {22, 41, 17, 46, 17, 48, 32, 48, 32, 46, 27, 41};
  PadPoints(tail, x_, y_);
  screen.DrawPolygon(tail, kRed);
  screen.DrawRectangle(x_ + 21, y_ + 12, 7, 5, kGreen);
  screen.DrawRectangle(x_ + 21, y_ + 17, 7, 5, kRed);
}

void Player::PadPoints(std::vector<int> &points, int pad_x, int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() - 1);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
