#include "HeightMapRaw.hpp"
#include "HeightMapGenerator.hpp"
#include <iostream>
void HeightMapRaw::showRawMap(HeightMapGenerator &heightMap) {
  for (auto row{heightMap.getFieldXY().begin()};
       row != heightMap.getFieldXY().end(); ++row) {
    std::cout << "[ ";
    for (auto col{row->begin()}; col != row->end(); ++col) {
      std::cout << *col << " ";
    }
    std::cout << "]\n";
  }
}