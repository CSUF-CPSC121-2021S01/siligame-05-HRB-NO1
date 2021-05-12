#ifndef GAME_H
#define GAME_H

#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game(int width, int height)
      : width_(width), height_(height), screen(width, height) {}

  Game() : Game(800, 600) {}

  graphics::Image &GetGameScreen() { return screen; }

  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return oppo; }

  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return oppopro;
  }

  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playpro;
  }

  Player &GetPlayer() { return player; }

  void CreateOpponents() {
    for (int i = 0; i < 2; i++) {
      Opponent opponent(50 + 100 * i, 50);
      std::unique_ptr<Opponent> opponentFactory =
          std::make_unique<Opponent>(10, 10);
      oppo.push_back(std::move(opponentFactory));
    }
  }

  void Init() {
    player.SetX(200);
    player.SetY(200);

    screen.AddMouseEventListener(*this);
    screen.AddAnimationEventListener(*this);
  }
  void MoveGameElements() {
    for (int d = 0; d < oppo.size(); d++) {
      if (oppo[d]->GetIsActive()) {
        oppo[d]->Move(screen);
      }
    }
    for (int e = 0; e < oppopro.size(); e++) {
      if (oppopro[e]->GetIsActive()) {
        oppopro[e]->Move(screen);
      }
    }
    for (int f = 0; f < playpro.size(); f++) {
      if (playpro[f]->GetIsActive()) {
        playpro[f]->Move(screen);
      }
    }
  }

  void FilterIntersections() {
    for (int g = 0; g < oppo.size(); g++) {
      if (player.GetIsActive() && oppo[g]->GetIsActive() &&
          player.IntersectsWith(oppo[g].get())) {
        oppo[g]->SetIsActive(false);
        player.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int h = 0; h < oppopro.size(); h++) {
      if (player.GetIsActive() && oppopro[h]->GetIsActive() &&
          player.IntersectsWith(oppopro[h].get())) {
        oppopro[h]->SetIsActive(false);
        player.SetIsActive(false);
        has_lost_ = true;
      }
    }
    for (int m = 0; m < playpro.size(); m++) {
      for (int l = 0; l < oppo.size(); l++) {
        if (playpro[m]->GetIsActive() && oppo[l]->GetIsActive() &&
            oppo[l]->IntersectsWith(playpro[m].get())) {
          playpro[m]->SetIsActive(false);
          oppo[l]->SetIsActive(false);
          if (player.GetIsActive()) {
            score_++;
          }
        }
      }
    }
  }

  void UpdateScreen() {
    screen.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
    screen.DrawText(1, 1, "Score:" + std::to_string(score_), 50, 0, 0, 0);
    for (int a = 0; a < oppo.size(); a++) {
      if (oppo[a]->GetIsActive()) {
        oppo[a]->Draw(screen);
      }
    }
    for (int b = 0; b < oppopro.size(); b++) {
      if (oppopro[b]->GetIsActive()) {
        oppopro[b]->Draw(screen);
      }
    }
    for (int c = 0; c < playpro.size(); c++) {
      if (playpro[c]->GetIsActive()) {
        playpro[c]->Draw(screen);
      }
    }
    if (player.GetIsActive()) {
      player.Draw(screen);
    } else {
      screen.DrawText(300, 200, "Game Over", 50, 0, 0, 0);
    }
  }

  void Start() { screen.ShowUntilClosed(); }

  void OnAnimationStep() {
    if (oppo.size() < 1) {
      CreateOpponents();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    RemoveInactive();
    UpdateScreen();
    screen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &mouseEvent) {
    if (mouseEvent.GetMouseAction() == graphics::MouseAction::kMoved ||
        mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
      int temp_x = player.GetX();
      int temp_y = player.GetY();
      player.SetX(mouseEvent.GetX() - player.GetWidth() / 2);
      player.SetY(mouseEvent.GetY() - player.GetHeight() / 2);
      if (player.GetX() > 800 || player.GetX() < 0) {
        player.SetX(temp_x);
      }
      if (player.GetY() > 600 || player.GetY() < 0) {
        player.SetY(temp_y);
      }
    }
    if (mouseEvent.GetMouseAction() == graphics::MouseAction::kPressed) {
      std::unique_ptr<PlayerProjectile> OnMouseEvent_oppo =
          std::make_unique<PlayerProjectile>(player.GetX(), player.GetY());
      playpro.push_back(std::move(OnMouseEvent_oppo));
    } else if (mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> OnMouseEvent_oppo =
          std::make_unique<PlayerProjectile>(player.GetX(), player.GetY());
      playpro.push_back(std::move(OnMouseEvent_oppo));
    }
  }

  int GetScore() { return score_; }
  bool HasLost() { return has_lost_; }
  void LaunchProjectiles() {
    for (int i = 0; i < oppo.size(); i++) {
      std::unique_ptr<OpponentProjectile> oppoFactory =
          oppo[i]->LaunchProjectile();
      if (oppoFactory != nullptr) {
        oppopro.push_back(std::move(oppoFactory));
      }
    }
  }

  void RemoveInactive() {
    for (int i = oppo.size() - 1; i >= 0; i--) {
      if (!oppo[i]->GetIsActive()) {
        oppo.erase(oppo.begin() + i);
      }
    }
    for (int j = oppopro.size() - 1; j >= 0; j--) {
      if (!oppopro[j]->GetIsActive()) {
        oppopro.erase(oppopro.begin() + j);
      }
    }
    for (int k = playpro.size() - 1; k >= 0; k--) {
      if (!playpro[k]->GetIsActive()) {
        playpro.erase(playpro.begin() + k);
      }
    }
  }

 private:
  graphics::Image screen;
  std::vector<std::unique_ptr<Opponent>> oppo;
  std::vector<std::unique_ptr<OpponentProjectile>> oppopro;
  std::vector<std::unique_ptr<PlayerProjectile>> playpro;
  Player player;
  int width_;
  int height_;
  int score_ = 0;
  bool has_lost_ = false;
};

#endif
