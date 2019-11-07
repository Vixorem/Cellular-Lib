#include "CrowdEngine.h"

void CrowdEngine::update() { changed_.clear(); }

t_cell CrowdEngine::at(int i, int j) { return cells_[h_ * i + j]; }

void CrowdEngine::set(int i, int j, Type t) { cells_[h_ * i + j] = t; }

void CrowdEngine::doAction(int i, int j) {
  // TODO: как обходить колонны?

  auto state = States::check_right;
  if (at(i, j) != Type::person) {
    return;
  }
  while (state != States::SIZE) {
    switch (state) {
      case check_right:
        if (j + 1 >= h_) {
          return;
        }
        if (at(i, j + 1) == Type::nothing) {
          changed_.insert(Ind{i, j + 1});
        }
        state = check_vertical;
        break;
      case check_vertical:
        if (i + 1 >= h_) {
          changed_.insert(Ind{i - 1, j});
        } else if (i - 1 < 0) {
          changed_.insert(Ind{i + 1, j});
        } else {
          if (at(i + 1, j) == Type::nothing && at(i - 1, j) == Type::nothing) {
            std::uniform_int_distribution<> direction(0, 1);
            auto d = direction(gen_);
            (d % 2) ? (changed_.insert(Ind{i + 1, j}))
                    : (changed_.insert(Ind{i - 1, j}));
          }
        }
        return;
      case SIZE:
        break;
      default:
        break;
    }
  }
}
