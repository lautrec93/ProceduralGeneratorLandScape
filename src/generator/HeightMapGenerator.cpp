#include "HeightMapGenerator.hpp"
#include <vector>

void HeightMapGenerator::fieldXYCreator(unsigned numberOfNodes) {
  for (unsigned i = 0; i < numberOfNodes; i++) {
    std::vector<double> rows;
    for (unsigned j = 0; j < numberOfNodes; j++) {
      rows.emplace_back(0.0);
    }
    fieldXY.emplace_back(rows);
  }
}

std::vector<std::vector<double>> &HeightMapGenerator::getFieldXY() {
  return fieldXY;
}
