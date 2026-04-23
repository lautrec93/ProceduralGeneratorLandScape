#include "generator/HeightMap/HeightMapBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/Noise/PerlinNoise.hpp"
#include <cstdio>
void HeightMapBuilder::heightMapBuilder() {
  heightMapContainer.heightMapResize(
      std::__math::pow(NUMBER_OF_NODES_IN_LINE, 2));
  for (unsigned i{0}; i < heightMapContainer.getHeightMap().size(); ++i) {
    for (unsigned j{0}; j < terrainConfig.octaveNumber; ++j) {
      heightMapContainer.getHeightMap()[i] +=
          fractalBrownianMotion.fractalBrownianMotionFunc(
              perlinNoise, i / NUMBER_OF_NODES_IN_LINE,
              i % NUMBER_OF_NODES_IN_LINE, j, terrainConfig.persistence,
              terrainConfig.lacunarity, terrainConfig.basicFrequency,
              terrainConfig.basicAmplitude);
    }
  }
  double min = heightMapContainer.getMin();
  double max = heightMapContainer.getMax();
  for (unsigned i{0}; i < heightMapContainer.getHeightMap().size(); ++i) {
    heightMapContainer.getHeightMap()[i] =
        postProcessor.normalizeFunction(i, min, max);
    heightMapContainer.getHeightMap()[i] =
        postProcessor.remapFunction(i, terrainConfig.coefficient);
    heightMapContainer.getHeightMap()[i] = postProcessor.scalingFunction(
        i, terrainConfig.minHeight, terrainConfig.maxHeight);
  }
}