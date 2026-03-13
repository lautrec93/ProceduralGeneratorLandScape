#pragma once

class Noise {

public:
  virtual void noise(unsigned nodes) = 0;
  virtual ~Noise() = default;
  virtual const double getValue() = 0;
};
