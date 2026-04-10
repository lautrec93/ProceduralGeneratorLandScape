#include "generator/HeightMap/HeightMapContainer.hpp"
#include "generator/Instruments/Globals.hpp"
#include <iostream>

std::vector<double> &HeightMapContainer::getHeightMap() {
  return heightMapContainer;
}
void HeightMapContainer::heightMapResize(unsigned size) {
  heightMapContainer.resize(std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2));
}

void HeightMapContainer::showMap() {
  std::cout << "[ ";
  for (unsigned i{0}; i < heightMapContainer.size(); ++i) {
    std::cout << " " << heightMapContainer[i];
    if (i % NUMBER_OF_NODES_IN_LINE == (NUMBER_OF_NODES_IN_LINE - 1) &&
        i != heightMapContainer.size() - 1) {
      std::cout << "]\n" << "[ ";
    }
  }
  std::cout << "]\n";
}

double HeightMapContainer::getMin() {
  double min{std::numeric_limits<double>::max()};
  for (unsigned i{0}; i < heightMapContainer.size(); ++i) {
    if (heightMapContainer[i] < min) {
      min = heightMapContainer[i];
    }
  }
  return min;
}

double HeightMapContainer::getMax() {
  double max{std::numeric_limits<double>::lowest()};
  for (unsigned i{0}; i < heightMapContainer.size(); ++i) {
    if (heightMapContainer[i] > max) {
      max = heightMapContainer[i];
    }
  }
  return max;
}

void HeightMapContainer::showMid() {
  double mid;
  for (unsigned i{0}; i < heightMapContainer.size(); ++i) {
    mid += heightMapContainer[i];
  }
  std::cout << mid / heightMapContainer.size() << "\n";
}
