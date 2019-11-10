#include "CrowdEngine.h"
#include <iostream>

using namespace states;
using namespace types;

void CrowdEngine::loadMap(int m) {
  people_out_ = 0;
  w_ = CrowdMap::win_w;
  h_ = CrowdMap::win_h;
  steps_ = 0;
  cells_.clear();
  cells_.resize(h_ * w_);
  people_num_ = CrowdMap::people_num;
  exit_ox_ = CrowdMap::exit_ox;

  for (auto& o : CrowdMap::walls) {
    for (int r = o.row; r < o.row + o.h; ++r) {
      for (int c = o.col; c < o.col + o.w; ++c) {
        set(r, c, Type::obstacle);
      }
    }
  }

  moveColumns(m);

  std::uniform_int_distribution<> ox(
      CrowdMap::people_rect.row,
      CrowdMap::people_rect.row + CrowdMap::people_rect.h - 1);
  std::uniform_int_distribution<> oy(
      CrowdMap::people_rect.col,
      CrowdMap::people_rect.col + CrowdMap::people_rect.w - 1);

  auto cnt = people_num_;
  while (cnt) {
    int i = ox(gen_);
    int j = oy(gen_);
    if (at(i, j) == Type::nothing) {
      set(i, j, Type::person);
      --cnt;
    }
  }
}

void CrowdEngine::update() {
  changed_.clear();

  if (!isFinished()) {
    for (int c = 0; c < w_; ++c) {
      for (int r = 0; r < h_; ++r) {
        doAction(r, c);
      }
    }

    for (int c = 0; c < w_; ++c) {
      for (int r = 0; r < h_; ++r) {
        if (changed_.find(std::make_pair(r, c)) != changed_.end()) {
          set(r, c, Type::person);
        }
      }
    }
  }

  ++steps_;
}

t_cell CrowdEngine::at(int i, int j) { return cells_[h_ * i + j]; }

void CrowdEngine::set(int i, int j, Type t) { cells_[h_ * i + j] = t; }

bool CrowdEngine::isFinished() { return people_out_ >= people_num_; }

int CrowdEngine::execute() {
  while (!isFinished()) {
    update();
  }

  return steps_;
}

size_t CrowdEngine::w() { return w_; }

size_t CrowdEngine::h() { return h_; }

void CrowdEngine::moveColumns(int m) {
  if (m == -1) {
    return;
  }
  for (auto& o : CrowdMap::columns) {
    for (int i = o.row; i < o.row + o.h; ++i) {
      for (int j = o.col; j < o.col + o.w; ++j) {
        set(i, j, Type::nothing);
      }
    }
  }
  for (int i = CrowdMap::columns[0].row;
       i < CrowdMap::columns[0].row + CrowdMap::columns[0].h; ++i) {
    for (int j = CrowdMap::columns[0].col;
         j < CrowdMap::columns[0].col + CrowdMap::columns[0].w; ++j) {
      set(i + m, j, Type::obstacle);
    }
  }
  for (int i = CrowdMap::columns[1].row;
       i < CrowdMap::columns[1].row + CrowdMap::columns[0].h; ++i) {
    for (int j = CrowdMap::columns[1].col;
         j < CrowdMap::columns[1].col + CrowdMap::columns[1].w; ++j) {
      set(i - m, j, Type::obstacle);
    }
  }
}

void CrowdEngine::doAction(int r, int c) {
  auto state = State::check_right;
  if (at(r, c) != Type::person ||
      changed_.find(std::make_pair(r, c)) != changed_.end()) {
    return;
  }

  while (state != states::SIZ) {
    switch (state) {
      case states::check_right:
        if (c + 1 >= w_) {
          state = states::check_vertical;
          break;
        }
        if (at(r, c + 1) == Type::nothing &&
            changed_.find(std::make_pair(r, c + 1)) == changed_.end()) {
          if (c + 1 >= exit_ox_) {
            ++people_out_;
            set(r, c, Type::nothing);
          } else {
            set(r, c, Type::nothing);
            changed_.insert(std::make_pair(r, c + 1));
          }
          return;
        }
        state = states::check_vertical;
        break;
      case states::check_vertical:
        if (r + 1 < h_ && r - 1 >= 0 && at(r + 1, c) == Type::nothing &&
            at(r - 1, c) == Type::nothing &&
            changed_.find(std::make_pair(r + 1, c)) == changed_.end() &&
            changed_.find(std::make_pair(r - 1, c)) == changed_.end()) {
          set(r, c, Type::nothing);
          std::uniform_int_distribution<> t(0, 1);
          if (t(gen_)) {
            changed_.insert(std::make_pair(r + 1, c));
          } else {
            changed_.insert(std::make_pair(r - 1, c));
          }
        } else if (r + 1 < h_ && at(r + 1, c) == Type::nothing &&
                   changed_.find(std::make_pair(r + 1, c)) == changed_.end()) {
          set(r, c, Type::nothing);
          changed_.insert(std::make_pair(r + 1, c));
        } else if (r - 1 >= 0 && at(r - 1, c) == Type::nothing &&
                   changed_.find(std::make_pair(r - 1, c)) == changed_.end()) {
          set(r, c, Type::nothing);
          changed_.insert(std::make_pair(r - 1, c));
        }

        return;
      case states::SIZ:
        return;
      default:
        return;
    }
  }
}
