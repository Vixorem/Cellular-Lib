#include "LifeEngine.h"

size_t module(int n, int m) { return (n % m + m) % m; }

LifeEngine::LifeEngine(size_t dim) : dim_(dim) { field_.resize(dim * dim); }

bool LifeEngine::at(size_t i, size_t j) {
  // TODO: range check

  return field_[dim_ * i + j];
}

void LifeEngine::set(size_t i, size_t j, bool value) {
  field_[dim_ * i + j] = value;
}

void LifeEngine::proceed() {
  std::vector<std::pair<size_t, size_t>> become_alive;
  std::vector<std::pair<size_t, size_t>> become_dead;

  for (size_t i = 0; i < dim_; ++i) {
    for (size_t j = 0; j < dim_; ++j) {
      if (!at(i, j) && getAliveNeighbours(i, j) == become_alive_) {
        become_alive.emplace_back(i, j);
      } else if (at(i, j) && stay_alive_.find(getAliveNeighbours(i, j)) ==
                                 stay_alive_.end()) {
        become_dead.emplace_back(i, j);
      }
    }
  }

  for (auto& p : become_alive) {
    set(p.first, p.second, true);
  }

  for (auto& p : become_dead) {
    set(p.first, p.second, false);
  }
}

size_t LifeEngine::getAliveNeighbours(int i, int j) {
  size_t counter = 0;
  for (int r = i - radius_; r <= i + radius_; ++r) {
    for (int c = j - radius_; c <= j + radius_; ++c) {
      if ((module(r - i, dim_) == module(c - j, dim_)) &&
          !diagonal_neighbour_) {
        continue;
      }
      if (r == i && c == j) {
        continue;
      }
      if (r < dim_ && c < dim_ && r >= 0 && c >= 0 && at(r, c)) {
        ++counter;
      }
      if (bound_type_ == life::BoundType::ENCLOSED &&
          (r < 0 || r >= dim_ || c < 0 || c >= dim_) &&
          at(module(r, dim_), module(c, dim_))) {
        ++counter;
        auto a = module(r, dim_);
        auto b = module(c, dim_);
      } else if (bound_type_ == life::BoundType::ALIVE_BOUND &&
                 (r < 0 || r >= dim_ || c < 0 || c >= dim_)) {
        ++counter;
      }
    }
  }

  return counter;
}

size_t LifeEngine::getDim() { return dim_; }
