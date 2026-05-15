#pragma once
#include "generator/MeshF/MeshStructs.hpp"
class SingleAngleNormalHandler {
public:
  double angleCount(float x1, float x2, float x, float y1, float y2, float y,
                    float z1, float z2, float z);
  Normal singleNormalCounter(float x1, float x2, float x, float y1, float y2,
                             float y, float z1, float z2, float z);
  SingleAngleNormalHandler() = default;
};