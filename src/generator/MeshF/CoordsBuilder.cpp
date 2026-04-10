#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include <iostream>
Coord CoordsBuilder::coordsCounting(unsigned index) {
  coord.x = (index / NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  coord.z = (index % NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  std::cout << "size = " << heightMapContainer.getHeightMap().size() << '\n';
  std::cout << "index = " << index << '\n';
  coord.y = heightMapContainer.getHeightMap()[index];

  return coord;
}