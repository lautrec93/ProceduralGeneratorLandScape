#pragma once

#include "NoiseParametres.hpp"

class Noise {

public:
  virtual void noise(const NoiseParametres &params) = 0;

  virtual double getValue() const = 0;
  virtual double getX() const = 0;
  virtual double getY() const = 0;
  virtual void changeX(double number) = 0;
  virtual void changeY(double number) = 0;

  virtual ~Noise() = default;
};
