#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "TerrainConfig.hpp"

class FractalBrownianMotion {
private:
  double baseAmplitude{1};
  double baseFrequency{1};
  HeightMapGenerator &hMap;
  TerrainConfig tConf;

public:
  std::vector<std::vector<double>> fractalBrownianMotion(Noise &noiseFunc);
  FractalBrownianMotion(HeightMapGenerator &hMap, TerrainConfig &tConf)
      : hMap(hMap), tConf(tConf) {}
};