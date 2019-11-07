#pragma once

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "LifeRules.h"

// Is supposed to be square
class LifeEngine {
 public:
  explicit LifeEngine(size_t dim);

  bool at(size_t i, size_t j);
  void set(size_t i, size_t j, bool value);

  // we have rules by default but can load different rules using this function
  bool loadRules(const std::string &path);
  bool loadSeed(const std::string &path);
  void proceed();
  size_t getAliveNeighbours(int i, int j);

  size_t getDim();

 private:
  size_t alive_cells_{0};
  size_t dim_;
  std::vector<bool> field_;

  int radius_{life::RADIUS};
  size_t become_alive_{life::BECOME_ALIVE};
  std::set<size_t> stay_alive_{life::STAY_ALIVE};
  life::BoundType bound_type_{life::BOUND_TYPE};
  bool diagonal_neighbour_ = life::DIAGONAL_NEIGHBOUR;
};
