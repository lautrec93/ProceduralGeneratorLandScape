#pragma once

#include "HeightMapRaw.hpp"
#include "TerrainConfig.hpp"
#include <vector>

class HeightMapGenerator {
private:
  HeightMapRaw heightMapRaw;
  TerrainConfig terrainConfig;
  unsigned coordX{};
  unsigned coordY{};
  unsigned numberOfNodes{};
  std::vector<std::vector<unsigned>> fieldXY;
  std::vector<std::vector<unsigned>>::iterator itera{fieldXY.begin()};
  double amplitude{};
  double frequency{};

public:
  void fieldXYCreator();
  double fractalBrownianMotion();
  virtual double noise() = 0;

  HeightMapGenerator(const TerrainConfig &config, unsigned x, unsigned y,
                     std::vector<std::vector<unsigned>> field,
                     std::vector<std::vector<unsigned>>::iterator iterator)
      : terrainConfig(config), coordX(x), coordY(y),
        numberOfNodes{
            static_cast<unsigned>(terrainConfig.size / terrainConfig.cellSize) -
            1},
        fieldXY(field), itera(iterator) {}
};