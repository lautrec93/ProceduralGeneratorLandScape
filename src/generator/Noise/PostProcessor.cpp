#include "generator/Noise/PostProcessor.hpp"
#include <cmath>

double PostProcessor::normalizeFunction(unsigned index, double min,
                                        double max) {
  double range = max - min;
  return (heightMapContainer.getHeightMap()[index] - min) / range;
}

double PostProcessor::remapFunction(unsigned index, double coefficient) {
  return std::__math::pow(heightMapContainer.getHeightMap()[index],
                          coefficient);
}

double PostProcessor::scalingFunction(unsigned index, double min, double max) {
  return heightMapContainer.getHeightMap()[index] * (max - min) + min;
}
