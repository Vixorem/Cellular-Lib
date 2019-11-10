#pragma once

#include <memory>
#include "../engine/CrowdEngine.h"
#include "../graphics/GraphicsManager.h"
#include "../graphics/widgets/Grid.h"
#include "core/BasicController.h"

class CrowdController : public BasicController {
 public:
  CrowdController(std::unique_ptr<GraphicsManager> manager);

  void update() override;
  void draw() override;
  void handleEvent(SDL_Event* e) override;

  void setCellSiz(size_t s);

 private:
  void initGrid();

  std::unique_ptr<GraphicsManager> manager_;
  std::shared_ptr<Grid> grid_;
  std::unique_ptr<CrowdEngine> engine_;
  SDL_Event* e_{nullptr};
  size_t cell_siz_ = 13;
};
