#include "FractalBrownianMotion.hpp"

void FractalBrownianMotion::fractalBrownianMotion(Noise &noiseFunc) {
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
  }
}