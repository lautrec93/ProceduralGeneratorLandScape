#pragma once

#include "TerrainConfig.hpp"
#include <optional>
#include <vector>
struct NoiseParametres {
  std::vector<std::vector<double>> &field;
  TerrainConfig terCon;

  std::optional<double> freq;
};