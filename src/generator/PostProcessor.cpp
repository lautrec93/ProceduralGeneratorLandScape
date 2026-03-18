#include "PostProcessor.hpp"
#include <algorithm>
#include <cmath>
#include <ranges>

void PostProcessor::normalizeFunction() {
  auto rangedHMap = finContainer.getValue() | std::views::join;
  auto [minEl, maxEl] = std::ranges::minmax_element(rangedHMap);
  double min = *minEl;
  double max = *maxEl;
  double range = max - min;
  for (double &value : rangedHMap) {
    value = (value - min) / range;
  }

  /*for (auto row{finContainer.getValue().begin()};
       row != finContainer.getValue().end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      *col = (*col - *minEl) / (*maxEl - *minEl);
    }
  }*/
}
void PostProcessor::remapFunction(double k) {
  auto rangedHMap = finContainer.getValue() | std::views::join;
  for (double &value : rangedHMap) {
    value = std::pow(value, k);
  }
}

void PostProcessor::scalingFunction(double min, double max) {
  auto rangedHMap = finContainer.getValue() | std::views::join;
  for (double &value : rangedHMap) {
    value = min + value * (max - min);
  }
}
