#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "xxhash.h"

class PerlinNoise : public Noise {
private:
  HeightMapGenerator heightMap_pn;
  double scaleXY{}; // could be changed in the future

public:
  void noise(unsigned nodes, std::vector<std::vector<double>> &field) override;
  PerlinNoise(float scale, HeightMapGenerator &heightMap)
      : scaleXY(scale), heightMap_pn(heightMap) {}
};