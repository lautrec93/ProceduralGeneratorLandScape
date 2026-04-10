#include "generator/MeshF/ColourBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <cmath>

Colour ColourBuilder::colourCounter(unsigned inddex) {}

double ColourBuilder::rChanalCounter(Normal &normal) {
  return 1.0 - std::__math::abs(normal.y);
}
double gChanalCounter(unsigned index, double height, double min, double max) {
  return (height - min) / (max - min);
}
double bChanalCounter(double height, double seaLevel, double min) {
  double beachTop = seaLevel + 3;
  return (height - min) / (beachTop - min);
}