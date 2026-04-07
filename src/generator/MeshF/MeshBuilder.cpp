#include "MeshBuilder.hpp"
#include "generator/Globals.hpp"

void MeshBuilder::meshBuild() {
  for (unsigned i{0}; i < 2 * std::pow(NUMBER_OF_NODES_IN_LINE - 1, 2); i++) {
    mesh.indices.push_back(indecesBuilder.evenPTT(i));
    mesh.indices.push_back(indecesBuilder.oddPTT(i));
  }
  mesh.vertices.resize(std::pow(NUMBER_OF_NODES_IN_LINE, 2));
  for (unsigned i{0}; i < std::pow(NUMBER_OF_NODES_IN_LINE, 2); i++) {
    mesh.vertices[i] = vertecesBuilder.vertexBuild(i);
  }
}