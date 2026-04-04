#include "generator/MeshF/UVBuilder.hpp"
#include "generator/Globals.hpp"
UV UVBuilder::uvCounter(unsigned index) {
  uv.u = ((index / NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize) /
         (5 * terrainConfig.cellSize);
  uv.v = ((index % NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize) /
         (5 * terrainConfig.cellSize);

  return uv;
}
