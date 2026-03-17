#pragma once
#include "generator/FractalBrownianMotion.hpp"
#include "generator/HeightMapGenerator.hpp"
#include "generator/HeightMapRawContainer.hpp"
#include "generator/NoiseParametres.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/SaveJSON.hpp"
#include "generator/TerrainConfig.hpp"
#include <random>
#include <vector>
int main() {
  TerrainConfig terrainMainConfig;
  terrainMainConfig.cellSize = 10;
  terrainMainConfig.size = 1000;
  terrainMainConfig.lacunarity = 2.0;
  terrainMainConfig.persistence = 0.5;
  terrainMainConfig.octaveNumber = 4;
  std::random_device rnd;
  std::mt19937 gen(rnd());
  std::uniform_int_distribution<> limits(100000000, 999999999);
  terrainMainConfig.seed = limits(gen);

  unsigned nodes = terrainMainConfig.size / terrainMainConfig.cellSize;

  HeightMapGenerator heightMainMapGenerator{terrainMainConfig};

  heightMainMapGenerator.fieldXYCreator(nodes);

  NoiseParametres perlinNoiseParam{heightMainMapGenerator.getFieldXY(),
                                   terrainMainConfig};

  PerlinNoise perlinNoise{0.05f, heightMainMapGenerator};

  FractalBrownianMotion fBM{heightMainMapGenerator, terrainMainConfig};
  auto finalHMap = fBM.fractalBrownianMotion(perlinNoise);

  HeightMapRawContainer<std::vector<std::vector<double>>> rawContainer(
      finalHMap);
  rawContainer.showRawMap();
  saveJSON(finalHMap, "heightmap.json");
}