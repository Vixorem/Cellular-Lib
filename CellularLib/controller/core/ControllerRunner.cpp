#include "ControllerRunner.h"

ControllerRunner::ControllerRunner(
    const std::vector<std::shared_ptr<BasicController>>& controllers) {
  std::copy(controllers.begin(), controllers.end(),
            std::back_inserter(controllers_));
}

ControllerRunner::ControllerRunner(
    std::shared_ptr<BasicController> controller) {
  controllers_.push_back(controller);
}

void ControllerRunner::add(std::shared_ptr<BasicController> controller) {
  controllers_.push_back(controller);
}

void ControllerRunner::add(
    const std::vector<std::shared_ptr<BasicController>>& controllers) {
  std::copy(controllers.begin(), controllers.end(),
            std::back_inserter(controllers_));
}

void ControllerRunner::run() {
  bool exit = false;
  SDL_Event e;
  while (!exit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        exit = true;
      }
      for (auto& c : controllers_) {
        c->handleEvent(&e);
      }
      for (auto& c : controllers_) {
        c->update();
      }
      for (auto& c : controllers_) {
        c->draw();
      }
    }
  }
}
