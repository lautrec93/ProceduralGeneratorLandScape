#pragma once

#include "generator/Noise/Noise.hpp"

class FractalBrownianMotion {
private:
  Noise &noise;

public:
  double fractalBrownianMotionFunc(Noise &noise, unsigned x, unsigned y,
                                   unsigned octave, double persistence,
                                   double lacunarity, double basicFrequency,
                                   double basicAmplitude);
  FractalBrownianMotion(Noise &noise) : noise(noise) {}
};