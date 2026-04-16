#pragma once
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/Noise/PerlinNoise.hpp"
class ColourBuilder {
private:
  PerlinNoise perlinNoise;

public:
  double rChanalCounter(Normal &normal);
  double gChanalCounter(double height, double min, double max);
  double bChanalCounter(double height, double seaLevel, double min);
  double aChanalCounter(unsigned index);
  ColourBuilder(PerlinNoise perlinNoise) : perlinNoise(perlinNoise) {};
};