#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "xxhash.h"

class PerlinNoise : public Noise {
private:
  HeightMapGenerator field2D;
  float scaleXY{}; // could be changed in the future

public:
  void noise() override;
  PerlinNoise(float scale, HeightMapGenerator &heightMap)
      : scaleXY(scale), field2D(heightMap) {}
};