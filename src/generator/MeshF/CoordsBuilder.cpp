#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/Globals.hpp"
Coord CoordsBuilder::coordsCounting(unsigned index) {
  coord.x = (index / NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  coord.z = (index % NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  coord.y = heightMapContainer.getHeightMap()[index / NUMBER_OF_NODES_IN_LINE]
                                             [index % NUMBER_OF_NODES_IN_LINE];

  return coord;
}