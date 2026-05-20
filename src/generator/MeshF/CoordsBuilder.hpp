#pragma once
#include "generator/HeightMap/HeightMapContainer.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/MeshF/MeshStructs.hpp"

class CoordsBuilder {
private:
  HeightMapContainer &heightMapContainer;
  TerrainConfig terrainConfig;

public:
  Coord coordsCounting(unsigned index);

  CoordsBuilder(HeightMapContainer &heightMapContainer,
                TerrainConfig terrainConfig)
      : heightMapContainer(heightMapContainer), terrainConfig(terrainConfig) {};
};