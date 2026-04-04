#pragma once
#include "MeshStructs.hpp"
#include <vector>

struct Mesh {
  std::vector<Indices> indices;
  std::vector<Vertices> vertices;
};
