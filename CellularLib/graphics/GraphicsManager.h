#pragma once

#include "core/Window.h"

class GraphicsManager {
 public:
  GraphicsManager(std::shared_ptr<Window> window);

  std::shared_ptr<Window> getWindow();

 private:
  std::shared_ptr<Window> window_;
};
