#pragma once
#include "HeightMapGenerator.hpp"

class HeightMapRaw {
private:
  HeightMapGenerator heightMP;

public:
  HeightMapRaw(const HeightMapGenerator &hMP) : heightMP(hMP) {};
  void showRawMap(HeightMapGenerator &heightMap);
};