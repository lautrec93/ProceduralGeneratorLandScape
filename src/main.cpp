#pragma once
#include "generator/HeightMapGenerator.hpp"
#include "generator/HeightMapRaw.hpp"
#include "generator/Noise.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/SaveJSON.hpp"
#include "generator/TerrainConfig.hpp"
#include <iostream>
int main() {
  TerrainConfig terrainMainConfig;
  terrainMainConfig.cellSize = 10;
  terrainMainConfig.size = 1000;
  terrainMainConfig.lacunarity = 2.0;
  terrainMainConfig.persistence = 0.5;
  terrainMainConfig.octaveNumber = 4;

  unsigned nodes = terrainMainConfig.size / terrainMainConfig.cellSize;

  HeightMapGenerator heightMainMapGenerator{terrainMainConfig};

  heightMainMapGenerator.fieldXYCreator(nodes);

  PerlinNoise perlinNoise{0.05f, heightMainMapGenerator};
  perlinNoise.noise(nodes, heightMainMapGenerator.getFieldXY());
  heightMainMapGenerator.fractalBrownianMotion(perlinNoise);

  HeightMapRaw heightMainMapRaw{heightMainMapGenerator};
  heightMainMapRaw.showRawMap(heightMainMapGenerator);
  saveJSON(heightMainMapGenerator.getFieldXY(), "heightmap.json");
}