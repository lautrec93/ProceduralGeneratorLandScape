
#include "FractalBrownianMotion.hpp"
#include "HeightMapContainer.hpp"
#include <algorithm>
#include <vector>

// std::vector<std::vector<double>>
void FractalBrownianMotion::fractalBrownianMotion(Noise &noiseFunc) {
  std::vector<std::vector<double>> fieldCopy =
      heightMapContainer.getHeightMap();
  for (int i = 0; i < tConf.octaveNumber; i++) {
    double currentAmplitude =
        tConf.baseAmplitude * std::pow(tConf.persistence, i);
    double currentFrequency =
        tConf.baseFrequency * std::pow(tConf.lacunarity, i);
    noiseFunc.noise({fieldCopy, tConf, currentFrequency});
    for (auto row{fieldCopy.begin()}; row != fieldCopy.end(); ++row) {
      for (auto col{row->begin()}; col != row->end(); ++col) {
        *col *= currentAmplitude;
      }
    }
    for (unsigned i{0}; i < heightMapContainer.getHeightMap().size(); i++) {
      std::transform(
          heightMapContainer.getHeightMap()[i].begin(),
          heightMapContainer.getHeightMap()[i].end(), fieldCopy[i].begin(),
          heightMapContainer.getHeightMap()[i].begin(), std::plus<double>());
    }
  }

  // return heightMapContainer.getHeightMap();
}