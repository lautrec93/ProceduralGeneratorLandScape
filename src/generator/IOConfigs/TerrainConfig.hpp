#pragma once

#include <cstdint>
#include <sys/types.h>

struct TerrainConfig {
  uint32_t seed{};
  unsigned size{};
  double cellSize{};

  double noizeScale{};
  double basicAmplitude{};
  double basicFrequency{};
  double coefficient{};

  unsigned octaveNumber{};
  double lacunarity{};
  double persistence{};

  double maxHeight{};
  double minHeight{};
  double seaLevel{};

  TerrainConfig(uint32_t seed, unsigned size, double cellSize,
                double noizeScale, double basicAmplitude, double basicFrequency,
                double coefficient, unsigned octaveNumber, double lacunarity,
                double persistence, double maxHeight, double minHeight,
                double seaLevel)
      : seed(seed), size(size), cellSize(cellSize), noizeScale(noizeScale),
        basicAmplitude(basicAmplitude), basicFrequency(basicFrequency),
        coefficient(coefficient), octaveNumber(octaveNumber),
        lacunarity(lacunarity), persistence(persistence), minHeight(minHeight),
        maxHeight(maxHeight), seaLevel(seaLevel) {}
};