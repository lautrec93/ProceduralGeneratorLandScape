#pragma once

class Noise {

public:
  virtual void noise() = 0;
  virtual ~Noise() = default;
  virtual const double getValue() const = 0;
};
