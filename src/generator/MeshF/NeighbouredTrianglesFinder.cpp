#include "generator/MeshF/NeighbouredTrianglesFinder.hpp"
#include "generator/Globals.hpp"
#include <cstddef>

std::vector<const Indices *> NeighbouredTrianglesFinder::trianglesPutter(
    const std::vector<Indices> &indices) {
  unsigned unix = 2 * NUMBER_OF_NODES_IN_LINE - 1;
  const Indices *trIndexPointer = &indices[0];
  // первый ряд:
  indexOfTriangles.push_back(trIndexPointer); // первый элемент
  ++trIndexPointer;
  indexOfTriangles.push_back(trIndexPointer);

  for (unsigned i{0}; i < NUMBER_OF_NODES_IN_LINE - 2; i++) { // средние
                                                              // элементы
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
  }

  indexOfTriangles.push_back(trIndexPointer); // последний элемент

  // серединные ряды:
  for (unsigned i{0}; i < NUMBER_OF_NODES_IN_LINE - 2; i++) {
    trIndexPointer -= (unix - 2); // первый элемент
    indexOfTriangles.push_back(trIndexPointer);
    trIndexPointer += (unix - 1);
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
    for (unsigned j{0}; j < NUMBER_OF_NODES_IN_LINE - 2;
         j++) { // средние элементы
      trIndexPointer -= unix;
      indexOfTriangles.push_back(trIndexPointer);
      ++trIndexPointer;
      indexOfTriangles.push_back(trIndexPointer);
      ++trIndexPointer;
      indexOfTriangles.push_back(trIndexPointer);
      trIndexPointer += (unix - 2);
      indexOfTriangles.push_back(trIndexPointer);
      ++trIndexPointer;
      indexOfTriangles.push_back(trIndexPointer);
      ++trIndexPointer;
      indexOfTriangles.push_back(trIndexPointer);
    }
    trIndexPointer -= unix; // последний элемент
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
    trIndexPointer -= (unix - 1);
    indexOfTriangles.push_back(trIndexPointer);
  }
  // последний ряд:
  trIndexPointer -= (unix - 2); // первый элемент
  indexOfTriangles.push_back(trIndexPointer);

  for (unsigned i{0}; i < NUMBER_OF_NODES_IN_LINE - 2; i++) { // средние
                                                              // элементы
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
    ++trIndexPointer;
    indexOfTriangles.push_back(trIndexPointer);
  }
  indexOfTriangles.push_back(trIndexPointer); // последний элемент
  ++trIndexPointer;
  indexOfTriangles.push_back(trIndexPointer);

  return indexOfTriangles;
}