#pragma once
#include "generator/MeshF/MeshStructs.hpp"
class SingleAngleNormalHandler {
public:
  double angleCount(unsigned x1, unsigned x2, unsigned x, unsigned z1,
                    unsigned z2, unsigned z, double y1, double y2, double y);
  Normal singleNormalCounter(unsigned x1, unsigned x2, unsigned x, unsigned z1,
                             unsigned z2, unsigned z, double y1, double y2,
                             double y);
  SingleAngleNormalHandler() = default;
};