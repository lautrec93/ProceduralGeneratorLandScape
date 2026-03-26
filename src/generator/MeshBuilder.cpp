#include "MeshBuilder.hpp"
#include "generator/HeightMapContainer.hpp"
#include "generator/TerrainConfig.hpp"

Coords MeshBuilder::PointTo3DConverter() {
  unsigned counter{0};
  for (unsigned i{0}; i < heightMapContainer.getHeightMap().size(); i++) {
    for (unsigned j{0}; j < heightMapContainer.getHeightMap()[i].size(); j++) {
      mesh.meshParams.indices[counter++].coords = CoordsCounting(i, j);
    }
  }
  return coords;
}

void MeshBuilder::PointsToTriangles() {
  for (unsigned i{0}; i < heightMapContainer.getHeightMap().size() - 1; i++) {
    for (unsigned j{0}; j < heightMapContainer.getHeightMap()[i].size() - 1;
         j++) {
      mesh.meshParams.vertices.push_back(evenPTT(i, j));
      mesh.meshParams.vertices.push_back(oddPTT(i, j));
    }
  }
}

Coords MeshBuilder::CoordsCounting(unsigned i, unsigned j) {
  coords.x = i * terrainConfig.cellSize;
  coords.z = j * terrainConfig.cellSize;
  coords.y = heightMapContainer.getHeightMap()[i][j];

  return this->coords;
}

Vertices MeshBuilder::evenPTT(unsigned i, unsigned j) {
  vertices.a = {i, j};
  vertices.b = {++i, j};
  vertices.c = {++i, ++j};

  return this->vertices;
}
Vertices MeshBuilder::oddPTT(unsigned i, unsigned j) {
  vertices.a = {i, j};
  vertices.b = {i, ++j};
  vertices.c = {++i, ++j};

  return this->vertices;
}