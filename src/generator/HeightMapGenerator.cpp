#pragma once

#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "TerrainConfig.hpp"
#include <vector>

void HeightMapGenerator::fieldXYCreator() {
  for (unsigned i = 0; i < numberOfNodes; i++) {
    std::vector<double> rows;
    for (unsigned j = 0; j < numberOfNodes; j++) {
      rows.emplace_back(0.0);
    }
    fieldXY.emplace_back(rows);
  }
}

double HeightMapGenerator::fractalBrownianMotion(Noise &noiseFunc) {
  for (int i = 0; i < terrainConfig.octaveNumber; i++) {
    amplitude *= noiseFunc.getValue();
    amplitude *= std::pow(terrainConfig.persistence, i);
    frequency *= std::pow(terrainConfig.lacunarity, i);
  }
}

const std::vector<std::vector<double>> &HeightMapGenerator::getFieldXY() const {
  return fieldXY;
}

HeightMapGenerator &HeightMapGenerator::operator*=(double other) {
  for (auto row{fieldXY.begin()}; row != fieldXY.end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      *col = amplitude * other;
    }
  }

  return *this;
}
