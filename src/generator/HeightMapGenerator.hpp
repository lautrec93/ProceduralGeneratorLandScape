#pragma once

#include "TerrainConfig.hpp"
#include <vector>

class HeightMapGenerator {
private:
  TerrainConfig terrainConfig;
  std::vector<std::vector<double>> fieldXY{};

public:
  void fieldXYCreator(unsigned numberOfNodes);
  std::vector<std::vector<double>> &getFieldXY();

  HeightMapGenerator(TerrainConfig &config) : terrainConfig(config) {}
};
