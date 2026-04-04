#include "generator/MeshF/NeighbouredTrianglesFinder.hpp"
#include "generator/Globals.hpp"

std::vector<std::vector<unsigned>>
NeighbouredTrianglesFinder::vertecesToIndeces(unsigned i) {
  for (unsigned i{0}; i < std::pow(NUMBER_OF_NODES_IN_LINE, 2); i++) {
    vertToInd[mesh.indices[i].a].push_back(i);
    vertToInd[mesh.indices[i].b].push_back(i);
    vertToInd[mesh.indices[i].c].push_back(i);
  }
  return vertToInd;
}
