#pragma once

#include <memory>
#include "../engine/LifeEngine.h"
#include "../graphics/GraphicsManager.h"
#include "../graphics/SolidObject.h"
#include "../graphics/core/Window.h"
#include "../graphics/widgets/Grid.h"
#include "core/BasicController.h"

class LifeController : public BasicController {
 public:
  LifeController(std::unique_ptr<GraphicsManager> manager,
                 std::unique_ptr<LifeEngine> universe);

  void handleEvent(SDL_Event* e) override;
  void update() override;
  void draw() override;

 private:
  void initGrid();

  std::unique_ptr<GraphicsManager> manager_;
  std::shared_ptr<Grid> grid_;
  std::unique_ptr<LifeEngine> universe_;

  SDL_Event* e_{nullptr};
};
