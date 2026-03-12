#pragma once

#include "TerrainConfig.hpp"
#include <vector>

class HeightMapGenerator {
private:
  TerrainConfig terrainConfig;
  unsigned coordX{};
  unsigned coordY{};
  unsigned numberOfNodes{};
  std::vector<std::vector<double>> fieldXY;
  std::vector<std::vector<double>>::iterator itera{fieldXY.begin()};
  double amplitude{};
  double frequency{};

public:
  void fieldXYCreator();
  double fractalBrownianMotion();
  const std::vector<std::vector<double>> &getFieldXY() const;

  HeightMapGenerator(const TerrainConfig &config, unsigned x, unsigned y,
                     std::vector<std::vector<double>> field,
                     std::vector<std::vector<double>>::iterator iterator)
      : terrainConfig(config), coordX(x), coordY(y),
        numberOfNodes{
            static_cast<unsigned>(terrainConfig.size / terrainConfig.cellSize) -
            1},
        fieldXY(field), itera(iterator) {}
};
