#pragma once

#include <set>

namespace life {

enum class BoundType { ENCLOSED, DEAD_BOUND, ALIVE_BOUND };

static int RADIUS = 1;
static size_t BECOME_ALIVE = 3;
static std::set<size_t> STAY_ALIVE = {2, 3};
static bool DIAGONAL_NEIGHBOUR = true;
static BoundType BOUND_TYPE = BoundType::ENCLOSED;

}  // namespace rule
