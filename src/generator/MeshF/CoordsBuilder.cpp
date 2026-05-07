#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/MeshF/MeshStructs.hpp"
Coord CoordsBuilder::coordsCounting(unsigned index) {
  Coord Coord;
  Coord.x = (index / NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  Coord.z = (index % NUMBER_OF_NODES_IN_LINE) * terrainConfig.cellSize;
  Coord.y = heightMapContainer.getHeightMap()[index];

  return Coord;
}