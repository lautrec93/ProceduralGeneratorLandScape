#include "HeightMapGenerator.hpp"
#include "TerrainConfig.hpp"
#include <vector>

void HeightMapGenerator::fieldXYCreator() {
  for (unsigned i = 0; i < numberOfNodes; i++) {
    std::vector<unsigned> rows;
    for (unsigned j = 0; j < numberOfNodes; j++) {
      rows.emplace_back(0);
    }
    fieldXY.emplace_back(rows);
  }
}

double HeightMapGenerator::fractalBrownianMotion() {
  for (int i = 0; i < terrainConfig.octaveNumber; i++) {
    for (; itera != fieldXY.end(); ++itera) {
      *itera = amplitude * noise()
    }
    amplitude *= std::pow(terrainConfig.persistence, i);
    frequency *= std::pow(terrainConfig.lacunarity, i);
  }
}
