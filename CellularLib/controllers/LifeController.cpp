#include "LifeController.h"

LifeController::LifeController(std::unique_ptr<GraphicsManager> manager,
                               std::unique_ptr<LifeEngine> universe)
    : manager_(std::move(manager)), universe_(std::move(universe)) {
  initGrid();
}

void LifeController::handleEvent(SDL_Event* e) {
  // todo: create a vector of functions in the future
  e_ = e;
}

void LifeController::update() {
  if (!e_) {
    return;
  }

  switch (e_->type) {
    case SDL_MOUSEBUTTONUP:
      int x, y;
      SDL_GetMouseState(&x, &y);
      auto ind = grid_->getClickedIndex(x, y);
      if (ind.i_ == -1 || ind.j_ == -1) {
        return;
      }

      universe_->set(ind.i_, ind.j_, !universe_->at(ind.i_, ind.j_));
      break;

    case SDL_KEYDOWN:
      universe_->proceed();
      break;
  }
}

void LifeController::draw() {
  SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), 193, 193, 193,
                         0);
  SDL_RenderClear(manager_->getWindow()->getRenderer());

  auto dim = universe_->getDim();
  for (size_t i = 0; i < dim; ++i) {
    for (size_t j = 0; j < dim; ++j) {
      auto pos = grid_->getPos(i, j);
      auto colour = (universe_->at(i, j)) ? (0) : (255);

      SDL_SetRenderDrawColor(manager_->getWindow()->getRenderer(), colour,
                             colour, colour, 0x00);
      SDL_Rect rect{pos.x_, pos.y_, grid_->getItemW(), grid_->getItemH()};
      SDL_RenderFillRect(manager_->getWindow()->getRenderer(), &rect);
    }
  }

  SDL_RenderPresent(manager_->getWindow()->getRenderer());
}

void LifeController::initGrid() {
  auto dim = universe_->getDim();
  auto w = manager_->getWindow()->getW();
  auto h = manager_->getWindow()->getH();

  grid_ = std::make_shared<Grid>(w, h, dim, dim, 1);
}
