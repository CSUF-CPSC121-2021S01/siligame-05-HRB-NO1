#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game game;
  game.Init();
  game.Start();

  return 0;
}
