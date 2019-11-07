#pragma once

#include <memory>
#include <vector>

#include "BasicController.h"

class ControllerRunner {
 public:
  ControllerRunner(
      const std::vector<std::shared_ptr<BasicController>>& controllers);
  ControllerRunner(std::shared_ptr<BasicController> controller);

  void add(std::shared_ptr<BasicController> controller);
  void add(const std::vector<std::shared_ptr<BasicController>>& controllers);

  void run();

 private:
  std::vector<std::shared_ptr<BasicController>> controllers_;
};
