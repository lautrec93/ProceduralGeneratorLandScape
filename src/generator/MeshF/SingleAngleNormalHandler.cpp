#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <algorithm>
#include <cmath>

double SingleAngleNormalHandler::angleCount(float x1, float x2, float x,
                                            float y1, float y2, float y,
                                            float z1, float z2, float z) {
  Coord vectorAB{x1 - x, y1 - y, z1 - z};
  Coord vectorAC{x2 - x, y2 - y, z2 - z};
  double scalarMultiply{vectorAB.x * vectorAC.x + vectorAB.y * vectorAC.y +
                        vectorAB.z * vectorAC.z};
  double vectABLength{std::sqrt(std::pow(vectorAB.x, 2) +
                                std::pow(vectorAB.y, 2) +
                                std::pow(vectorAB.z, 2))};
  double vectACLength{std::sqrt(std::pow(vectorAC.x, 2) +
                                std::pow(vectorAC.y, 2) +
                                std::pow(vectorAC.z, 2))};
  double cosinus =
      std::clamp(scalarMultiply / (vectABLength * vectACLength), -1.0, 1.0);
  double arccosinus = std::acos(cosinus);
  return arccosinus;
}

Normal SingleAngleNormalHandler::singleNormalCounter(float x1, float x2,
                                                     float x, float y1,
                                                     float y2, float y,
                                                     float z1, float z2,
                                                     float z) {
  Normal vectorAB{x1 - x, y1 - y, z1 - z};
  Normal vectorAC{x2 - x, y2 - y, z2 - z};
  Normal singleNormal{vectorAB.z * vectorAC.y - vectorAB.y * vectorAC.z,
                      vectorAB.x * vectorAC.z - vectorAB.z * vectorAC.x,
                      vectorAB.y * vectorAC.x - vectorAB.x * vectorAC.y};

  return singleNormal;
}