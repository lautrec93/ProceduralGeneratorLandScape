#pragma once

#include "Noise.hpp"
#include "TerrainConfig.hpp"
#include <vector>

class HeightMapGenerator {
private:
  TerrainConfig terrainConfig;
  std::vector<std::vector<double>> fieldXY{};
  double amplitude{};
  double frequency{};

public:
  void fieldXYCreator(unsigned numberOfNodes);
  void fractalBrownianMotion(Noise &noiseFunc);
  std::vector<std::vector<double>> &getFieldXY();
  HeightMapGenerator &operator*=(double other);

  HeightMapGenerator(TerrainConfig &config) : terrainConfig(config) {}
};
