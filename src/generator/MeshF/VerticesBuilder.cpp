#include "generator/MeshF/VerticesBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"

Vertices VerticesBuilder::vertexBuild(unsigned index) {
  Vertices Vertex;
  Vertex.coord = coordBuilder.coordsCounting(index);
  Vertex.normal = normalBuilder.normalSummation(index);
  Vertex.uv = uvBuilder.uvCounter(index);
  Vertex.colour.RSlope = colourBuilder.rChanalCounter(vertex.normal);
  Vertex.colour.GHeight = colourBuilder.gChanalCounter(
      vertex.coord.y, terrainConfig.minHeight, terrainConfig.maxHeight);
  Vertex.colour.BDepth = colourBuilder.bChanalCounter(
      vertex.coord.y, terrainConfig.seaLevel, terrainConfig.minHeight);
  Vertex.colour.aBiome = colourBuilder.aChanalCounter(index);
  return Vertex;
}
