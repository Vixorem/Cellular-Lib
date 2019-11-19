#include "CrowdController.h"
#include "../seeds/CrowdSeeds.h"

CrowdController::CrowdController(std::unique_ptr<GraphicsManager> manager) {
  manager_ = std::move(manager);
  engine_ = std::make_unique<CrowdEngine>();
  engine_->loadMap(0);
  initGrid();
}

void CrowdController::update() {
  if (!e_) {
    return;
  }

  switch (e_->type) {
    case SDL_KEYDOWN:
      engine_->update();
      break;
  }
}

void CrowdController::draw() {
  SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), 193, 193, 193,
                         0);
  SDL_RenderClear(manager_->getWindow()->getRenderer());
  auto w = engine_->w();
  auto h = engine_->h();
  for (size_t i = 0; i < h; ++i) {
    for (size_t j = 0; j < w; ++j) {
      auto pos = grid_->getPos(i, j);
      auto t = engine_->at(i, j);

      switch (t) {
        case types::Type::nothing:
          SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), 255, 255,
                                 255, 0x00);
          break;
        case types::Type::person:
          SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), 61, 236,
                                 245, 0x00);
          break;
        case types::Type::obstacle:
          SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), 56, 56,
                                 55, 0x00);
          break;
      }
      SDL_Rect rect{pos.x_, pos.y_, grid_->getItemW(), grid_->getItemH()};
      SDL_RenderFillRect(manager_->getWindow()->getRenderer(), &rect);
    }
  }

  SDL_RenderPresent(manager_->getWindow()->getRenderer());
}

void CrowdController::handleEvent(SDL_Event* e) { e_ = e; }

void CrowdController::setCellSiz(size_t s) { cell_siz_ = s; }

void CrowdController::initGrid() {
  auto w = engine_->w();
  auto h = engine_->h();
  auto space = 1;
  auto win_w = w * (cell_siz_ + space);
  auto win_h = h * (cell_siz_ + space);

  grid_ = std::make_shared<Grid>(win_w, win_h, w, h, space);
  manager_->getWindow()->resize(win_w, win_h);
}
