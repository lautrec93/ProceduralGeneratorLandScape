#pragma once
#include "HeightMapFinContainer.hpp"
#include "generator/TerrainConfig.hpp"
#include <vector>
class PostProcessor {
private:
  HeightMapFinContainer<std::vector<std::vector<double>>> &finContainer;
  TerrainConfig terrConf;

public:
  void normalizeFunction();
  void remapFunction(double k);
  void scalingFunction(double min, double max);

  PostProcessor(
      HeightMapFinContainer<std::vector<std::vector<double>>> &finContainer)
      : finContainer(finContainer) {};
};