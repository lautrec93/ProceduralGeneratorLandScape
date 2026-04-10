#pragma once

class Noise {

public:
  virtual double noiseFunc(double x, double y) = 0;

  virtual ~Noise() = default;
};
