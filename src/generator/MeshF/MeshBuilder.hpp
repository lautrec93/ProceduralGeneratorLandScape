#pragma once

#include "generator/MeshF/IndicesBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/VerticesBuilder.hpp"
class MeshBuilder {
private:
  Mesh &mesh;
  IndicesBuilder indicesBuilder;
  VerticesBuilder verticesBuilder;

public:
  void meshBuild();
  MeshBuilder(Mesh &mesh, VerticesBuilder verticesBuilder)
      : mesh(mesh), verticesBuilder(verticesBuilder) {};
};