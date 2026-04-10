#pragma once

#include "Noise.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"

class PerlinNoise : public Noise {
private:
  TerrainConfig terrainConfig;

public:
  double noiseFunc(double x, double y) override;
  PerlinNoise(const TerrainConfig terrainConfig)
      : terrainConfig(terrainConfig) {};
};