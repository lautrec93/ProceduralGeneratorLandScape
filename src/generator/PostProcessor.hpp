#pragma once

#include "generator/HeightMapContainer.hpp"
class PostProcessor {
private:
  HeightMapContainer &heightMapContainer;

public:
  void normalizeFunction();
  void remapFunction(double k);
  void scalingFunction(double min, double max);

  PostProcessor(HeightMapContainer &heightMapContainer)
      : heightMapContainer(heightMapContainer) {};
};