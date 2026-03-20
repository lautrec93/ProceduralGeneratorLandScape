#include "generator/HeightMapContainer.hpp"
#include <iostream>

std::vector<std::vector<double>> &HeightMapContainer::getHeightMap() {
  return heightMap;
}
void HeightMapContainer::showMap() {
  for (auto row{heightMap.begin()}; row != heightMap.end(); ++row) {
    std::cout << "[ ";
    for (auto col{row->begin()}; col != row->end(); ++col) {
      std::cout << *col << " ";
    }
    std::cout << "]\n";
  }
}
void HeightMapContainer::showMin() {
  double min{1};
  for (auto row{heightMap.begin()}; row != heightMap.end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      if (*col <= min) {
        min = *col;
      }
    }
  }
  std::cout << min << "\n";
}
void HeightMapContainer::showMax() {
  double max{-1};
  for (auto row{heightMap.begin()}; row != heightMap.end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      if (*col >= max) {
        max = *col;
      }
    }
  }
  std::cout << max << "\n";
}

void HeightMapContainer::showMid(double size) {
  double mid{};
  for (auto row{heightMap.begin()}; row != heightMap.end(); ++row) {
    for (auto col{row->begin()}; col != row->end(); ++col) {
      mid += *col;
    }
  }
  std::cout << mid / size << "\n";
}
