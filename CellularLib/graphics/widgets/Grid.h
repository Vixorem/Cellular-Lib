#pragma once

struct Point {
  size_t x_;
  size_t y_;
};

struct Index {
  int i_;
  int j_;
};

class Grid {
 public:
  Grid(size_t win_w, size_t win_h, size_t hor_cells_cnt, size_t ver_cells_cnt,
       size_t space);

  Point getPos(size_t i, size_t j);
  Point getPos();
  size_t getItemH();
  size_t getItemW();

  void setPos(const Point& p);
  Index getClickedIndex(int x, int y);

 private:
  size_t space_;
  size_t w_;
  size_t h_;
  size_t vert_siz_;
  size_t hor_siz_;
  size_t item_h_{0};
  size_t item_w_{0};
  Point pos_{0, 0};
};
