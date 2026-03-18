#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "TerrainConfig.hpp"

class FractalBrownianMotion {
private:
  double baseAmplitude{1.0};
  double baseFrequency{0.01};
  HeightMapGenerator &hMap;
  TerrainConfig tConf;

public:
  std::vector<std::vector<double>> fractalBrownianMotion(Noise &noiseFunc);
  FractalBrownianMotion(HeightMapGenerator &hMap, TerrainConfig &tConf)
      : hMap(hMap), tConf(tConf) {}
};