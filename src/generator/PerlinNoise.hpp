#pragma once

#include "Noise.hpp"
#include "xxhash.h"

class PerlinNoise : public Noise {
private:
  double scaleXY{};
  double value{};
  double x{};
  double y{};

public:
  void noise(const NoiseParametres &params) override;
  double getValue() const override;
  double getX() const override;
  double getY() const override;
  void changeX(double number) override;
  void changeY(double number) override;
};