#pragma once
#include "generator/HeightMapGenerator.hpp"
#include "generator/HeightMapRaw.hpp"
#include "generator/Noise.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/TerrainConfig.hpp"
#include <iostream>
int main() {
  TerrainConfig terrainMainConfig;
  terrainMainConfig.cellSize = 10;
  terrainMainConfig.size = 100;
  terrainMainConfig.lacunarity = 2.0;
  terrainMainConfig.persistence = 0.5;
  terrainMainConfig.octaveNumber = 4;

  unsigned nodes = terrainMainConfig.size / terrainMainConfig.cellSize - 1;

  HeightMapGenerator heightMainMapGenerator{terrainMainConfig};

  heightMainMapGenerator.fieldXYCreator(nodes);

  // PerlinNoise perlinNoise{0.01, heightMainMapGenerator};
  // perlinNoise.noise(nodes);
  // heightMainMapGenerator.fractalBrownianMotion(perlinNoise);

  HeightMapRaw heightMainMapRaw{heightMainMapGenerator};
  heightMainMapRaw.showRawMap(heightMainMapGenerator);
}