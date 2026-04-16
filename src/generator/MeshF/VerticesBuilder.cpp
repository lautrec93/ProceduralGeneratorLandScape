#include "generator/MeshF/VerticesBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"

Vertices VerticesBuilder::vertexBuild(unsigned index) {
  vertex.coord = coordBuilder.coordsCounting(index);
  vertex.normal = normalBuilder.normalSummation(index);
  vertex.uv = uvBuilder.uvCounter(index);
  vertex.colour.RSlope = colourBuilder.rChanalCounter(vertex.normal);
  vertex.colour.GHeight = colourBuilder.gChanalCounter(
      vertex.coord.y, terrainConfig.minHeight, terrainConfig.maxHeight);
  vertex.colour.BDepth = colourBuilder.bChanalCounter(
      vertex.coord.y, terrainConfig.seaLevel, terrainConfig.minHeight);
  vertex.colour.aBiome = colourBuilder.aChanalCounter(index);
  return vertex;
}
