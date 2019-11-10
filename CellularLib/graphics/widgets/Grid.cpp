#include "Grid.h"

Grid::Grid(size_t win_w, size_t win_h, size_t hor_siz, size_t vert_siz,
           size_t space)
    : w_(win_w),
      h_(win_h),
      hor_siz_(hor_siz),
      vert_siz_(vert_siz),
      space_(space) {
  item_h_ = (h_ - space * (vert_siz - 1)) / vert_siz_;
  item_w_ = (w_ - space * (hor_siz - 1)) / hor_siz_;
}

Point Grid::getPos(size_t i, size_t j) {
  Point p;
  p.x_ = (pos_.x_ + item_w_ * i + space_ * (i + 1));
  p.y_ = (pos_.y_ + item_h_ * j + space_ * (j + 1));
  return p;
}

Point Grid::getPos() { return pos_; }

size_t Grid::getItemH() { return item_h_; }

size_t Grid::getItemW() { return item_w_; }

void Grid::setPos(const Point& p) { pos_ = p; }

Index Grid::getClickedIndex(int x, int y) {
  if (x < 0 || x > w_ || y < 0 || y > h_) {
    return Index{-1, -1};
  }

  Index ind{-1, -1};
  for (size_t i = 0; i < hor_siz_; ++i) {
    if (x > getPos(i, 0).x_ && x < getPos(i, 0).x_ + item_w_) {
      ind.i_ = i;
      break;
    }
  }

  for (size_t j = 0; j < vert_siz_; ++j) {
    if (y > getPos(0, j).y_ && y < getPos(0, j).y_ + item_h_) {
      ind.j_ = j;
      break;
    }
  }

  return ind;
}
