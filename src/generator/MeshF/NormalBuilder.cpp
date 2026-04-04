#include "NormalBuilder.hpp"
#include "generator/Globals.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <vector>

Normal NormalBuilder::normalSummation(unsigned index) {
  Normal finalNormal{};
  unsigned numberOfTriangles = nTF.vertecesToIndeces(index)[index].size();
  for (unsigned i{0}; i < numberOfTriangles; i++) {
    finalNormal.operator+=(normalProcessing(i));
  }
  double normalLength{std::sqrt(std::pow(finalNormal.x, 2) +
                                std::pow(finalNormal.z, 2) +
                                std::pow(finalNormal.y, 2))};
  finalNormal = {finalNormal.x / normalLength, finalNormal.z / normalLength,
                 finalNormal.y / normalLength};
  return finalNormal;
}

Normal NormalBuilder::normalProcessing(unsigned triangleIndex) {
  Coord currentCoordA =
      coordBuilder.coordsCounting(mesh.indices[triangleIndex].a);
  Coord currentCoordB =
      coordBuilder.coordsCounting(mesh.indices[triangleIndex].b);
  Coord currentCoordC =
      coordBuilder.coordsCounting(mesh.indices[triangleIndex].c);
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
