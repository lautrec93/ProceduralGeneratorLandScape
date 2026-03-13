#include "HeightMapGenerator.hpp"
#include "Noise.hpp"
#include "TerrainConfig.hpp"
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

void HeightMapGenerator::fractalBrownianMotion(Noise &noiseFunc) {
  for (int i = 0; i < terrainConfig.octaveNumber; i++) {
    double currentAmplitude =
        amplitude * std::pow(terrainConfig.persistence, i);
    double currentFrequency = frequency * std::pow(terrainConfig.lacunarity, i);
    // getFieldXY() // should realize it
    //  probably should add frequency into noise func
    //  this func should only multiply ready heightmap after Perlin
  }
}

std::vector<std::vector<double>> &HeightMapGenerator::getFieldXY() {
  return fieldXY;
}

HeightMapGenerator &
HeightMapGenerator::operator*=(double other) { // should change
  for (auto row{fieldXY.begin()}; row != fieldXY.end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      *col = amplitude * other;
    }
  }

  return *this;
}
