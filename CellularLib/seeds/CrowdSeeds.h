#pragma once
#include <vector>

struct Rect {
  int row;
  int col;
  int w;
  int h;
};

struct CrowdMap {
  static constexpr size_t win_w = 55;
  static constexpr size_t win_h = 55;
  static constexpr size_t room_w = 50;
  static constexpr size_t room_h = 30;
  static constexpr size_t grid_space = 1;
  static constexpr size_t cell_size = 10;
  static constexpr Rect walls[5] = {
      Rect{5, 5, room_w, 1}, Rect{36, 5, room_w, 1}, Rect{6, 5, 1, room_h}};
  static constexpr Rect columns[2] = {Rect{6, 3 + room_w, 2, 1},
                                      Rect{35, 3 + room_w, 2, 1}};

  static constexpr size_t exit_ox = 4 + room_w;
  static constexpr size_t people_num = 150;
  static constexpr Rect people_rect{6, 6, 28, 30};
};