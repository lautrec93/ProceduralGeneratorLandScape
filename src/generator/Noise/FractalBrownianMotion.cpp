#include "generator/Noise/FractalBrownianMotion.hpp"
#include "generator/Noise/Noise.hpp"
#include <cmath>

double FractalBrownianMotion::fractalBrownianMotionFunc(
    Noise &noise, unsigned x, unsigned y, unsigned octave, double persistence,
    double lacunarity, double basicFrequency, double basicAmplitude) {
  double frequency = basicFrequency * std::__math::pow(lacunarity, octave);
  double amplitude = basicAmplitude * std::__math::pow(persistence, octave);
  return noise.noiseFunc(x * frequency, y * frequency) * amplitude;
}