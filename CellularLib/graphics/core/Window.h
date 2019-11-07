#pragma once

#include <memory>

#include <string>
#include "Graphics.h"

class Window : Graphics {
 public:
  Window(size_t width, size_t height,
         const std::string& title = "Game of Life");

  ~Window();

  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();

  size_t getW();
  size_t getH();

 private:
  size_t width_;
  size_t height_;

  SDL_Window* sdl_window_;
  SDL_Renderer* sdl_renderer_;
};
