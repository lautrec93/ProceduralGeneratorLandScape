#pragma once

#include <cstdint>
#include <sys/types.h>

struct TerrainConfig {
  uint32_t seed{};
  unsigned size{};
  float cellSize{};

  float noizeScale{};

  unsigned octaveNumber{};
  float lacunarity{};
  float persistence{};

  float maxHeight{};
  float minHeight{};
  float seaLevel{};

  TerrainConfig(uint32_t seed, unsigned size, float cellSize, float noizeScale,
                unsigned octaveNumber, float lacunarity, float persistence,
                float maxHeight, float minHeight, float seaLevel)
      : seed(seed), size(size), cellSize(cellSize), noizeScale(noizeScale),
        octaveNumber(octaveNumber), lacunarity(lacunarity),
        persistence(persistence), minHeight(minHeight), maxHeight(maxHeight),
        seaLevel(seaLevel) {}
};