#pragma once

#include <cstdint>
#include <sys/types.h>

struct TerrainConfig {
  uint32_t seed{};
  unsigned size{};
  float cellSize{};

  float noizeScale{};
  float baseAmplitude{};
  float baseFrequency{};
  float coefficient{};

  unsigned octaveNumber{};
  float lacunarity{};
  float persistence{};

  float maxHeight{};
  float minHeight{};
  float seaLevel{};

  TerrainConfig(uint32_t seed, unsigned size, float cellSize,
                float baseAmplitude, float baseFrequency, float noizeScale,
                float coefficient, unsigned octaveNumber, float lacunarity,
                float persistence, float maxHeight, float minHeight,
                float seaLevel)
      : seed(seed), size(size), cellSize(cellSize),
        baseAmplitude(baseAmplitude), baseFrequency(baseFrequency),
        noizeScale(noizeScale), coefficient(coefficient),
        octaveNumber(octaveNumber), lacunarity(lacunarity),
        persistence(persistence), minHeight(minHeight), maxHeight(maxHeight),
        seaLevel(seaLevel) {}
};