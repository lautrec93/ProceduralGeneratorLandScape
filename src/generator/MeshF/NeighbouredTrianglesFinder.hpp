#pragma once
#include "generator/MeshF/Mesh.hpp"
#include "generator/TerrainConfig.hpp"
#include <vector>
class NeighbouredTrianglesFinder {
private:
  TerrainConfig terrainConfig;
  std::vector<std::vector<unsigned>> vertToInd;
  Mesh &mesh;

public:
  std::vector<std::vector<unsigned>> vertecesToIndeces(unsigned i);

  NeighbouredTrianglesFinder(Mesh &mesh, TerrainConfig terrainConfig)
      : mesh(mesh), terrainConfig(terrainConfig) {};
};