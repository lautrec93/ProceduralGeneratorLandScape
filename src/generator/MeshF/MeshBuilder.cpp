#include "generator/MeshF/MeshBuilder.hpp"
#include "generator/Instruments/Globals.hpp"

void MeshBuilder::meshBuild() {
  for (unsigned i{0}; i < std::__math::pow(NUMBER_OF_NODES_IN_LINE - 1, 2);
       ++i) {
    mesh.indices.push_back(indicesBuilder.evenPTT(i));
    mesh.indices.push_back(indicesBuilder.oddPTT(i));
  }
  mesh.vertices.resize(std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2));
  for (unsigned i{0}; i < std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2); ++i) {
    mesh.vertices[i] = verticesBuilder.vertexBuild(i);
  }
}