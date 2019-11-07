#include "controllers/LifeController.h"
#include "controllers/core/ControllerRunner.h"
#include "engine/LifeEngine.h"
#include "graphics/GraphicsManager.h"
#include "graphics/core/Window.h"

int main(int argc, char *args[]) {
  auto window = std::make_shared<Window>(750, 750);
  auto graphics_manager = std::make_unique<GraphicsManager>(window);
  auto life_engine = std::make_unique<LifeEngine>(50);
  auto life_controller =
      new LifeController(std::move(graphics_manager), std::move(life_engine));

  ControllerRunner runner(std::static_pointer_cast<BasicController>(
      std::shared_ptr<LifeController>(life_controller)));

  runner.run();

  return 0;
}