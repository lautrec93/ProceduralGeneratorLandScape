#pragma once

#include "generator/IOConfigs/TerrainConfig.hpp"
#include <string>
#include <vector>

class Input {
private:
  unsigned size{40000};
  double cellSize{10};
  double noizeScale{1.0};
  double baseAmplitude{1.0};
  double baseFrequency{0.01};
  double coefficient{2.5};
  unsigned octaveNumber{4};
  double lacunarity{2.0};
  double persistence{0.5};
  double maxHeight{4000};
  double minHeight{-1000};
  double seaLevel{0.0};
  std::string primarySeed;
  uint32_t seed;

  bool ifSeedNum(std::string &primarySeed);

public:
  std::vector<TerrainConfig> startInput();
  Input() {}
};