#pragma once

#include <vector>
class HeightMapContainer {
private:
  std::vector<double> heightMapContainer;

public:
  std::vector<double> &getHeightMap();
  void heightMapResize(unsigned size);
  HeightMapContainer() = default;

  void showMap();
  double getMin();
  double getMax();
  void showMid();
};