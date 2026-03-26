#pragma once
#include "Mesh.hpp"
#include "generator/HeightMapContainer.hpp"
#include "generator/TerrainConfig.hpp"

class MeshBuilder {
private:
  HeightMapContainer heightMapContainer;
  TerrainConfig terrainConfig;
  Coords coords;
  Vertices vertices;
  Mesh mesh;

public:
  Coords PointTo3DConverter();

  void PointsToTriangles();
  Vertices evenPTT(unsigned i, unsigned j);
  Vertices oddPTT(unsigned i, unsigned j);
  Coords CoordsCounting(unsigned i, unsigned j);
  MeshBuilder(HeightMapContainer heightMapContainer, Mesh mesh,
              TerrainConfig terrainConfig)
      : heightMapContainer(heightMapContainer), mesh(mesh),
        terrainConfig(terrainConfig) {}
};