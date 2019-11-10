#pragma once
#include <random>
#include <set>
#include <vector>
#include "../seeds/CrowdSeeds.h"

typedef unsigned char t_cell;

namespace states {
enum State { check_right, check_vertical, SIZ };
}

namespace types {
enum Type { nothing, person, obstacle, SIZ };
}

using namespace states;
using namespace types;

class CrowdEngine {
 public:
  void loadMap(int m = 0);

  void update();
  t_cell at(int i, int j);
  void set(int i, int j, Type t);
  bool isFinished();
  int execute();
  size_t w();
  size_t h();
  void moveColumns(int m);

 private:
  void doAction(int i, int j);

  std::vector<Type> cells_;
  size_t w_;
  size_t h_;
  size_t people_num_;
  size_t exit_ox_;
  std::random_device rd;
  std::mt19937 gen_{rd()};
  std::set<std::pair<int, int>> changed_;
  size_t steps_{0};

  size_t people_out_{0};
};

