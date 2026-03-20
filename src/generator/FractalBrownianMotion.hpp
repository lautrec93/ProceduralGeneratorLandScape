#pragma once

#include "Noise.hpp"
#include "TerrainConfig.hpp"
#include "generator/HeightMapContainer.hpp"

class FractalBrownianMotion {
private:
  HeightMapContainer &heightMapContainer;
  TerrainConfig tConf;

public:
  // std::vector<std::vector<double>>
  void fractalBrownianMotion(Noise &noiseFunc);
  FractalBrownianMotion(HeightMapContainer &heightMapContainer,
                        TerrainConfig tConf)
      : heightMapContainer(heightMapContainer), tConf(tConf) {}
};