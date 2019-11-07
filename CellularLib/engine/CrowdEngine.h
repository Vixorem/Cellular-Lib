#pragma once
#include <random>
#include <vector>
#include <set>

typedef unsigned char t_cell;

enum States { check_right, check_vertical, SIZE };

enum Type { nothing, person, obstacle, SIZE };

struct Ind {
  int i;
  int j;
};

class CrowdEngine {
 public:
  template <class T>
  void loadMap();

  void update();
  t_cell at(int i, int j);
  void set(int i, int j, Type t);

 private:
  void doAction(int i, int j);

  std::set<Ind> changed_;
  std::vector<Type> cells_;
  size_t w_;
  size_t h_;
  size_t people_num;
  std::mt19937 gen_;
};

template <class T>
inline void CrowdEngine::loadMap() {
  w_ = T::w;
  h_ = T::h;
  cells_.resize(h_ * w_);
  people_num = T::people_num;

  for (auto& o : T::obstacles) {
    for (int i = o.x; i < o.x + o.w; ++i) {
      for (int j = o.y; j < o.y + o.h; ++j) {
        set(i, j, obstacle);
      }
    }
  }

  std::uniform_int_distribution<> ox(T::people_rect.x,
                                     T::people_rect.x + T::people_rect.w);
  std::uniform_int_distribution<> oy(T::people_rect.y,
                                     T::people_rect.y + T::people_rect.h);

  auto cnt = people_num;
  while (cnt) {
    int i = ox(gen_);
    int j = oy(gen_);
    if (at(i, j) == Type::nothing) {
      set(i, j, person);
      --cnt;
    }
  }
}
