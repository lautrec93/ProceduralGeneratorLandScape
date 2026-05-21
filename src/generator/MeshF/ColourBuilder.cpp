#include "generator/MeshF/ColourBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <algorithm>
#include <cmath>

double ColourBuilder::rChanalCounter(Normal &normal) {
  return pow(1.0 - std::__math::abs(normal.y), 2);
}
double ColourBuilder::gChanalCounter(double height, double min, double max) {
  return pow((height - min) / (max - min), 2);
}
double ColourBuilder::bChanalCounter(double height, double seaLevel,
                                     double min) {
  double beachTop = seaLevel + 3;
  return pow(
      1 - std::max(std::min((beachTop - height) / (beachTop - min), 1.0), 0.0),
      2);
}

double ColourBuilder::aChanalCounter(unsigned index) {
  double biome = perlinNoise.noiseFunc(
      (index / NUMBER_OF_NODES_IN_LINE + 52228) * 0.00025,
      (index % NUMBER_OF_NODES_IN_LINE + 22852) * 0.00025);
  return std::pow(biome, 2);
}