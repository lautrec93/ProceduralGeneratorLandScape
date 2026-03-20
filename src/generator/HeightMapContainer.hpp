#pragma once

#include <vector>
class HeightMapContainer {
private:
  std::vector<std::vector<double>> heightMap;

public:
  std::vector<std::vector<double>> &getHeightMap();
  HeightMapContainer(std::vector<std::vector<double>> heightMap)
      : heightMap(heightMap) {};

  void showMap();
  void showMin();
  void showMax();
  void showMid(double size);
};