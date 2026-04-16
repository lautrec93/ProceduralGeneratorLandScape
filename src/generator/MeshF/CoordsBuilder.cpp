#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
Coord CoordsBuilder::coordsCounting(unsigned index) {
  coord.x = (index / NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  coord.z = (index % NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  coord.y = heightMapContainer.getHeightMap()[index];

  return coord;
}