#include "FractalBrownianMotion.hpp"
#include <algorithm>
#include <vector>

std::vector<std::vector<double>>
FractalBrownianMotion::fractalBrownianMotion(Noise &noiseFunc) {
  std::vector<std::vector<double>> fieldCopy = hMap.getFieldXY();
  for (int i = 0; i < tConf.octaveNumber; i++) {
    double currentAmplitude = baseAmplitude * std::pow(tConf.persistence, i);
    double currentFrequency = baseFrequency * std::pow(tConf.lacunarity, i);
    noiseFunc.noise({hMap.getFieldXY(), tConf, currentFrequency});
    for (auto row{hMap.getFieldXY().begin()}; row != hMap.getFieldXY().end();
         ++row) {
      for (auto col{row->begin()}; col != row->end(); ++col) {
        *col *= currentAmplitude;
      }
    }
    for (unsigned i{0}; i < hMap.getFieldXY().size(); i++) {
      std::transform(fieldCopy[i].begin(), fieldCopy[i].end(),
                     hMap.getFieldXY()[i].begin(), fieldCopy[i].begin(),
                     std::plus<double>());
    }
  }
  hMap.getFieldXY().clear();
  hMap.getFieldXY().shrink_to_fit();
  return fieldCopy;
}