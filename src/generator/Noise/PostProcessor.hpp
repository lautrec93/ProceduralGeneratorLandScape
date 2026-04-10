#pragma once

#include "generator/HeightMap/HeightMapContainer.hpp"
class PostProcessor {
private:
  HeightMapContainer &heightMapContainer;

public:
  double normalizeFunction(unsigned index, double min, double max);
  double remapFunction(unsigned index, double coefficient);
  double scalingFunction(unsigned index, double min, double max);

  PostProcessor(HeightMapContainer &heightMapContainer)
      : heightMapContainer(heightMapContainer) {};
};