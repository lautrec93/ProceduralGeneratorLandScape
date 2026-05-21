#include "generator/MeshF/VerticesBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"

Vertices VerticesBuilder::vertexBuild(unsigned index) {
  Vertices Vertex;
  Vertex.coord = coordBuilder.coordsCounting(index);
  Vertex.normal = normalBuilder.normalSummation(index);
  Vertex.uv = uvBuilder.uvCounter(index);
  Vertex.colour.RSlope = colourBuilder.rChanalCounter(Vertex.normal);
  Vertex.colour.GHeight = colourBuilder.gChanalCounter(
      Vertex.coord.y, terrainConfig.minHeight, terrainConfig.maxHeight);
  Vertex.colour.BDepth = colourBuilder.bChanalCounter(
      Vertex.coord.y, terrainConfig.seaLevel, terrainConfig.minHeight);
  Vertex.colour.aBiome = colourBuilder.aChanalCounter(index);
  return Vertex;
}
