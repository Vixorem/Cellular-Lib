#include "Graphics.h"

Graphics::Graphics() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      // Couldn't initialize
  }
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      //Linear filtering is not enabled (but we can continue)
  }
}
