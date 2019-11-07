#include "Window.h"

Window::Window(size_t width, size_t height,
               const std::string& title)
    : Graphics(), width_(width), height_(height) {
  sdl_window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, width_, height_,
                                 SDL_WINDOW_SHOWN);
  if (sdl_window_ == nullptr) {
    // Couldn't create window
  }

  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

  if (sdl_renderer_ == nullptr) {
    // Couldn't create renderer
  }

  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    // Couldn't init SDL_image
  }
}

Window::~Window() {
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);
  sdl_window_ = nullptr;
  sdl_renderer_ = nullptr;

  IMG_Quit();
  SDL_Quit();
}

SDL_Window* Window::getWindow() { return sdl_window_; }

SDL_Renderer* Window::getRenderer() { return sdl_renderer_; }

size_t Window::getW() { return width_; }

size_t Window::getH() { return height_; }

