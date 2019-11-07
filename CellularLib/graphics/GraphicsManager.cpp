#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(std::shared_ptr<Window> window)
    : window_(window) {}


std::shared_ptr<Window> GraphicsManager::getWindow() {
  return window_;
}
