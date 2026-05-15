#include "generator/MeshF/MeshBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include <iostream>

void MeshBuilder::meshBuild() {
  std::cout << "NODES: " << NUMBER_OF_NODES_IN_LINE << "\n";
  for (unsigned i{0}; i <= (std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2) - 1) -
                               (NUMBER_OF_NODES_IN_LINE + 1);
       ++i) {
    if ((((i + 1) % NUMBER_OF_NODES_IN_LINE) == 0) && (i - 1) != 0) {
      continue;
    }
    mesh.indices.push_back(indicesBuilder.evenPTT(i));
    mesh.indices.push_back(indicesBuilder.oddPTT(i));
  }

  const unsigned total = std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2);
  mesh.vertices.resize(total);
#pragma omp parallel for schedule(dynamic, 64)
  for (unsigned i = 0; i < total; ++i) {
    mesh.vertices[i] = verticesBuilder.vertexBuild(i);
  }
}