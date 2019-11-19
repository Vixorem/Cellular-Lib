#include <iostream>
#include "controllers/CrowdController.h"
#include "controllers/LifeController.h"
#include "controllers/core/ControllerRunner.h"
#include "engine/CrowdEngine.h"
#include "engine/LifeEngine.h"
#include "graphics/GraphicsManager.h"
#include "graphics/core/Window.h"
#include "seeds/CrowdSeeds.h"

int main(int argc, char* args[]) {
  // auto window = std::make_shared<Window>(700, 500);
  // auto graphics_manager = std::make_unique<GraphicsManager>(window);
  //// auto life_engine = std::make_unique<LifeEngine>(50);
  // auto controller = new CrowdController(std::move(graphics_manager));

  // ControllerRunner runner(std::static_pointer_cast<BasicController>(
  //    std::shared_ptr<CrowdController>(controller)));

  // runner.run();

  CrowdEngine engine;
  size_t sum = 0;
  int count = 10;

  int res;

  for (int i = 0; i < 15; ++i) {
    size_t sum = 0;
    for (int k = 0; k < count; ++k) {
      engine.loadMap(i);
      int tmp = engine.execute();
      sum += tmp;
    }
    std::cout << sum / count << std::endl;
  }

  //std::cout << "done\n";

  return 0;
}