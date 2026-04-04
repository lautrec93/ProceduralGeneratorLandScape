#pragma once

#include "generator/MeshF/IndicesBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/VerticesBuilder.hpp"
class MeshBuilder {
private:
  Mesh &mesh;
  IndicesBuilder indecesBuilder;
  VerticesBuilder vertecesBuilder;

public:
  void meshBuild();
  MeshBuilder(Mesh &mesh, VerticesBuilder vertecesBuilder)
      : mesh(mesh), vertecesBuilder(vertecesBuilder) {};
};