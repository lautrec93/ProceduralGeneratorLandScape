#include "generator/MeshF/IndicesBuilder.hpp"
#include "generator/Instruments/Globals.hpp"

Indices IndicesBuilder::evenPTT(unsigned index) {
  triangleIndex.a =
      (index / NUMBER_OF_NODES_IN_LINE) * NUMBER_OF_NODES_IN_LINE +
      (index % NUMBER_OF_NODES_IN_LINE);
  triangleIndex.b =
      ((index / NUMBER_OF_NODES_IN_LINE) + 1) * NUMBER_OF_NODES_IN_LINE +
      (index % NUMBER_OF_NODES_IN_LINE);
  triangleIndex.c =
      ((index / NUMBER_OF_NODES_IN_LINE) + 1) * NUMBER_OF_NODES_IN_LINE +
      ((index % NUMBER_OF_NODES_IN_LINE) + 1);

  return triangleIndex;
}

Indices IndicesBuilder::oddPTT(unsigned index) {
  triangleIndex.a =
      (index / NUMBER_OF_NODES_IN_LINE) * NUMBER_OF_NODES_IN_LINE +
      (index % NUMBER_OF_NODES_IN_LINE);
  triangleIndex.b =
      (index / NUMBER_OF_NODES_IN_LINE) * NUMBER_OF_NODES_IN_LINE +
      ((index % NUMBER_OF_NODES_IN_LINE) + 1);
  triangleIndex.c =
      ((index / NUMBER_OF_NODES_IN_LINE) + 1) * NUMBER_OF_NODES_IN_LINE +
      ((index % NUMBER_OF_NODES_IN_LINE) + 1);

  return triangleIndex;
}
