#pragma once
#include <SDL_image.h>

class BasicController {
 public:
  virtual void update() = 0;
  virtual void handleEvent(SDL_Event* e) = 0;
  virtual void draw() = 0;
};
