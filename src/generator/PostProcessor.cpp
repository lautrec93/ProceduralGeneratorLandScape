#include "PostProcessor.hpp"
#include <algorithm>
#include <cmath>
#include <ranges>

void PostProcessor::normalizeFunction() {
  auto rangedHMap = heightMapContainer.getHeightMap() | std::views::join;
  auto [minEl, maxEl] = std::ranges::minmax_element(rangedHMap);
  double min = *minEl;
  double max = *maxEl;
  double range = max - min;
  for (double &value : rangedHMap) {
    value = (value - min) / range;
  }
}
void PostProcessor::remapFunction(double k) {
  auto rangedHMap = heightMapContainer.getHeightMap() | std::views::join;
  for (double &value : rangedHMap) {
    value = std::pow(value, k);
  }
}

void PostProcessor::scalingFunction(double min, double max) {
  auto rangedHMap = heightMapContainer.getHeightMap() | std::views::join;
  for (double &value : rangedHMap) {
    value = min + value * (max - min);
  }
}
