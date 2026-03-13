#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "xxhash.h"

class PerlinNoise : public Noise {
private:
  HeightMapGenerator heightMap_pn;
  float scaleXY{}; // could be changed in the future

public:
  void noise(unsigned nodes) override;
  PerlinNoise(float scale, HeightMapGenerator &heightMap)
      : scaleXY(scale), heightMap_pn(heightMap) {}
};