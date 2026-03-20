#pragma once

#include "TerrainConfig.hpp"
#include <string>
#include <vector>

class Input {
private:
  float cellSize = 10;
  unsigned size = 40000;
  float noizeScale = 1.0;
  float lacunarity = 2.0;
  float persistence = 0.5;
  unsigned octaveNumber = 4;
  float minHeight = -1000;
  float maxHeight = 4000;
  float seaLevel = 0.25;
  std::string primarySeed;
  uint32_t seed;

  bool ifSeedNum(std::string &primarySeed);

public:
  std::vector<TerrainConfig> startInput();
  Input() {}
};