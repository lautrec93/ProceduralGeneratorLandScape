#pragma once
#include "generator/FractalBrownianMotion.hpp"
#include "generator/HeightMapFinContainer.hpp"
#include "generator/HeightMapGenerator.hpp"
#include "generator/HeightMapRawContainer.hpp"
#include "generator/NoiseParametres.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/PostProcessor.hpp"
#include "generator/SaveJSON.hpp"
#include "generator/TerrainConfig.hpp"
#include <random>
#include <vector>
int main() {
  TerrainConfig terrainMainConfig;
  terrainMainConfig.cellSize = 10;
  terrainMainConfig.size = 40000;
  terrainMainConfig.lacunarity = 2.0;
  terrainMainConfig.persistence = 0.5;
  terrainMainConfig.octaveNumber = 4;
  terrainMainConfig.minHeight = -1000;
  terrainMainConfig.maxHeight = 4000;
  terrainMainConfig.seaLevel = 0.25;
  std::random_device rnd;
  std::mt19937 gen(rnd());
  std::uniform_int_distribution<> limits(100000000, 999999999);
  terrainMainConfig.seed = limits(gen);

  unsigned nodes = terrainMainConfig.size / terrainMainConfig.cellSize;
  double coefficient = 2.5;

  HeightMapGenerator heightMainMapGenerator{terrainMainConfig};

  heightMainMapGenerator.fieldXYCreator(nodes);

  NoiseParametres perlinNoiseParam{heightMainMapGenerator.getFieldXY(),
                                   terrainMainConfig};

  PerlinNoise perlinNoise{0.05f, heightMainMapGenerator};

  FractalBrownianMotion fBM{heightMainMapGenerator, terrainMainConfig};
  auto finalHMap = fBM.fractalBrownianMotion(perlinNoise);

  HeightMapRawContainer<std::vector<std::vector<double>>> rawContainer(
      finalHMap);
  HeightMapFinContainer<std::vector<std::vector<double>>> finContainer(
      rawContainer.getValue());
  PostProcessor postProc{finContainer};
  postProc.normalizeFunction();
  postProc.remapFunction(coefficient);
  postProc.scalingFunction(terrainMainConfig.minHeight,
                           terrainMainConfig.maxHeight);
  finContainer.showRawMap();
  finContainer.showMin();
  finContainer.showMax();
  finContainer.showMid(std::pow(nodes, 2));
  saveJSON(finContainer.getValue(), "heightmap.json");
}