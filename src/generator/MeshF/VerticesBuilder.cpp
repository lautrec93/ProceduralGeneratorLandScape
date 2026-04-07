#include "generator/MeshF/VerticesBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"

Vertices VerticesBuilder::vertexBuild(unsigned index) {
  vertex.coord = coordBuilder.coordsCounting(index);
  vertex.normal = normalBuilder.normalSummation(index);
  vertex.uv = uvBuilder.uvCounter(index);

  return vertex;
}
