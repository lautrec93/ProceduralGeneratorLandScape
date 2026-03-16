#pragma once

#include <vector>
class Noise {

public:
  virtual void noise(unsigned nodes,
                     std::vector<std::vector<double>> &field) = 0;
  virtual ~Noise() = default;
};
