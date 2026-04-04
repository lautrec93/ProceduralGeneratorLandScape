#pragma once
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/MeshF/NeighbouredTrianglesFinder.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/TerrainConfig.hpp"
class NormalBuilder {
private:
  TerrainConfig terrainConfig;
  CoordsBuilder coordBuilder;
  NeighbouredTrianglesFinder &nTF;
  SingleAngleNormalHandler &sANH;
  Mesh &mesh;
  Normal normalProcessing(unsigned triangleIndex);

public:
  Normal normalSummation(unsigned index);

  NormalBuilder(Mesh &mesh, TerrainConfig terrainConfig,
                CoordsBuilder coordBuilder, NeighbouredTrianglesFinder &nTF,
                SingleAngleNormalHandler &sANH)
      : mesh(mesh), terrainConfig(terrainConfig), coordBuilder(coordBuilder),
        nTF(nTF), sANH(sANH) {};
};