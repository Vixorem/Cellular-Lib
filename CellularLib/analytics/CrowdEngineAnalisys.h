#pragma once
#include "../engine/CrowdEngine.h"

class CrowdEngineAnalisys {
 public:
  static size_t getMean(CrowdEngine& engine, size_t count) {
    size_t sum = 0;

    for (int i = 0; i < count; ++i) {
      sum += engine.execute();
      engine.loadMap();
      engine.moveColumns(i);
    }

    return sum / count;
  }
};
