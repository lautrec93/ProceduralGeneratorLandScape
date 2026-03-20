#include "HeightMapGenerator.hpp"
#include <vector>

std::vector<std::vector<double>>
HeightMapGenerator::fieldXYCreator(unsigned numberOfNodes) {
  std::vector<std::vector<double>> heightMap;
  for (unsigned i{0}; i < numberOfNodes; i++) {
    std::vector<double> rows;
    for (unsigned j = 0; j < numberOfNodes; j++) {
      rows.emplace_back(0.0);
    }
    heightMap.emplace_back(rows);
  }
  return heightMap;
}
