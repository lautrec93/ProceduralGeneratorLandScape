#pragma once

#include "TerrainConfig.hpp"
#include <vector>

class HeightMapGenerator {
private:
  TerrainConfig terrainConfig;

public:
  std::vector<std::vector<double>> fieldXYCreator(unsigned numberOfNodes);

  HeightMapGenerator(TerrainConfig config) : terrainConfig(config) {}
};
