#pragma once
#include "generator/MeshF/MeshStructs.hpp"
#include <cstddef>
#include <vector>
class NeighbouredTrianglesFinder {
private:
  std::vector<const Indices *> indexOfTriangles;

public:
  std::vector<const Indices *>
  trianglesPutter(const std::vector<Indices> &indices);

  NeighbouredTrianglesFinder() = default;
};
