#include "NormalBuilder.hpp"
#include "generator/Globals.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <vector>

Normal NormalBuilder::normalSummation(
    unsigned index) { // тут мы принимаем индекс конкретной вершины, возвращаем
                      // нормаль для каждого ее треуголльника и суммируем их +
                      // нормализуем

  Normal finalNormal{};
  std::vector<const Indices *> listOfTrianglesOfPoints =
      nTF.trianglesPutter(mesh.indices);
  indPtr = &listOfTrianglesOfPoints[0];

  for (unsigned i{0}; i < countNumberOfTriangles(mesh.indices.size(), index);
       i++) {

    finalNormal += (normalProcessing(**indPtr));
    ++indPtr;
  }

  double normalLength{std::sqrt(std::pow(finalNormal.x, 2) +
                                std::pow(finalNormal.z, 2) +
                                std::pow(finalNormal.y, 2))};
  finalNormal = {finalNormal.x / normalLength, finalNormal.z / normalLength,
                 finalNormal.y / normalLength};
  return finalNormal;
}

Normal NormalBuilder::normalProcessing(
    const Indices &triangle) { // тут берем треугольник по адресу и для него
                               // считаем координаты, угол, нормаль и возвращаем
                               // отскейленную, готовую к суммированию нормаль
  Coord currentCoordA = coordBuilder.coordsCounting(triangle.a);
  Coord currentCoordB = coordBuilder.coordsCounting(triangle.b);
  Coord currentCoordC = coordBuilder.coordsCounting(triangle.c);
  double angle =
      sANH.angleCount(currentCoordB.x, currentCoordC.x, currentCoordA.x,
                      currentCoordB.z, currentCoordC.z, currentCoordA.z,
                      currentCoordB.y, currentCoordC.y, currentCoordA.y);
  Normal normal = sANH.singleNormalCounter(
      currentCoordB.x, currentCoordC.x, currentCoordA.x, currentCoordB.z,
      currentCoordC.z, currentCoordA.z, currentCoordB.y, currentCoordC.y,
      currentCoordA.y);
  Normal scaledNormal = {normal.x * angle, normal.z * angle, normal.y * angle};

  return scaledNormal;
}

unsigned NormalBuilder::countNumberOfTriangles(unsigned size, unsigned index) {

  if (size - index == NUMBER_OF_NODES_IN_LINE ||
      index == NUMBER_OF_NODES_IN_LINE - 1) {
    return 1;

  } else if (index > NUMBER_OF_NODES_IN_LINE && index < size - index &&
             (index % NUMBER_OF_NODES_IN_LINE > 0 &&
              index % NUMBER_OF_NODES_IN_LINE < NUMBER_OF_NODES_IN_LINE - 1)) {
    return 6;

  } else {
    return 3;
  }
}
