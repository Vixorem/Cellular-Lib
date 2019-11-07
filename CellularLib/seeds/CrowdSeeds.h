#pragma once
#include <vector>

struct Rect {
  int x;
  int y;
  int w;
  int h;
};

struct Crowd1 {
  size_t w = 80;
  size_t h = 50;
  size_t grid_space = 1;
  size_t cell_size = 10;
  std::vector<Rect> obstacles{Rect{10, 10, 50, 1}, Rect{10, 40, 50, 1}};
  size_t people_num = 150;
  Rect people_rect{11, 11, 25, 25};
};