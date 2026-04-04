#pragma once
#include "generator/HeightMapContainer.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/TerrainConfig.hpp"

class CoordsBuilder {
private:
  HeightMapContainer &heightMapContainer;
  TerrainConfig terrainConfig;
  Coord coord;

public:
  Coord coordsCounting(unsigned index);

  CoordsBuilder(HeightMapContainer &heightMapContainer,
                TerrainConfig terrainConfig)
      : heightMapContainer(heightMapContainer), terrainConfig(terrainConfig) {};
};