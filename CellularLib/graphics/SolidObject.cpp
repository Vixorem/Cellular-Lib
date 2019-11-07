#include "SolidObject.h"

SolidObject::SolidObject(SDL_Renderer* renderer, const SDL_Rect* rect)
    : renderer_(renderer), rect_(rect) {}

void SolidObject::draw() { SDL_RenderFillRect(renderer_, rect_); }
