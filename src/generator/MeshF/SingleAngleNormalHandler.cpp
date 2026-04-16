#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <algorithm>
#include <cmath>

double SingleAngleNormalHandler::angleCount(unsigned x1, unsigned x2,
                                            unsigned x, unsigned z1,
                                            unsigned z2, unsigned z, double y1,
                                            double y2, double y) {
  Coord vectorAB{x1 - x, z1 - z, static_cast<float>(y1 - y)};
  Coord vectorAC{x2 - x, z2 - z, static_cast<float>(y2 - y)};
  double scalarMultiply{vectorAB.x * vectorAC.x + vectorAB.z * vectorAC.z +
                        vectorAB.y * vectorAC.y};
  double vectABLength{std::sqrt(std::pow(vectorAB.x, 2) +
                                std::pow(vectorAB.z, 2) +
                                std::pow(vectorAB.y, 2))};
  double vectACLength{std::sqrt(std::pow(vectorAC.x, 2) +
                                std::pow(vectorAC.z, 2) +
                                std::pow(vectorAC.y, 2))};
  double cosinus =
      std::clamp(scalarMultiply / (vectABLength * vectACLength), -1.0, 1.0);
  double arccosinus = std::acos(cosinus);
  return arccosinus;
}

Normal SingleAngleNormalHandler::singleNormalCounter(unsigned x1, unsigned x2,
                                                     unsigned x, unsigned z1,
                                                     unsigned z2, unsigned z,
                                                     double y1, double y2,
                                                     double y) {
  Normal vectorAB{static_cast<float>(x1 - x), static_cast<float>(z1 - z),
                  static_cast<float>(y1 - y)};
  Normal vectorAC{static_cast<float>(x2 - x), static_cast<float>(z2 - z),
                  static_cast<float>(y2 - y)};
  Normal singleNormal{vectorAB.z * vectorAC.y - vectorAB.y * vectorAC.z,
                      vectorAB.y * vectorAC.x - vectorAB.x * vectorAC.y,
                      vectorAB.x * vectorAC.z - vectorAB.z * vectorAC.x};

  return singleNormal;
}