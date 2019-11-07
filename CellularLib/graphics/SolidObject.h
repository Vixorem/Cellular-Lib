#pragma once

#include <SDL.h>
#include "core/BasicObject.h"
#include "widgets/Grid.h"

class SolidObject : public BasicObject {
 public:
  SolidObject(SDL_Renderer* renderer, const SDL_Rect* rect);

  void update() override {}
  void draw() override;

 private:
  SDL_Renderer* renderer_;
  const SDL_Rect* rect_;
};