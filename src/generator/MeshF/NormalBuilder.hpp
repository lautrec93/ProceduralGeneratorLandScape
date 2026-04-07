#pragma once
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/MeshF/NeighbouredTrianglesFinder.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
class NormalBuilder {
private:
  CoordsBuilder coordBuilder;
  NeighbouredTrianglesFinder &nTF;
  SingleAngleNormalHandler &sANH;
  Mesh &mesh;
  const Indices **indPtr = nullptr;
  Normal normalProcessing(const Indices &triangle);
  unsigned countNumberOfTriangles(unsigned size, unsigned index);

public:
  Normal normalSummation(unsigned index);

  NormalBuilder(Mesh &mesh, CoordsBuilder coordBuilder,
                NeighbouredTrianglesFinder &nTF, SingleAngleNormalHandler &sANH)
      : mesh(mesh), coordBuilder(coordBuilder), nTF(nTF), sANH(sANH) {};
};