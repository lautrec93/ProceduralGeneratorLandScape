#include "generator/HeightMap/HeightMapBuilder.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/Noise/PerlinNoise.hpp"
#include <cmath>
#include <cstdio>
void HeightMapBuilder::heightMapBuilder() {
  heightMapContainer.heightMapResize(std::pow(NUMBER_OF_NODES_IN_LINE, 2));
#pragma omp parallel for collapse(2) schedule(static)
  for (unsigned i = 0; i < heightMapContainer.getHeightMap().size(); ++i) {
    for (unsigned j = 0; j < terrainConfig.octaveNumber; ++j) {
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

#pragma omp parallel for
  for (unsigned i = 0; i < heightMapContainer.getHeightMap().size(); ++i) {
    heightMapContainer.getHeightMap()[i] =
        postProcessor.normalizeFunction(i, min, max);
    heightMapContainer.getHeightMap()[i] =
        postProcessor.remapFunction(i, terrainConfig.coefficient);
    heightMapContainer.getHeightMap()[i] = postProcessor.scalingFunction(
        i, terrainConfig.minHeight, terrainConfig.maxHeight);
  }
}