#include "generator/HeightMap/HeightMapContainer.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/Noise/FractalBrownianMotion.hpp"
#include "generator/Noise/PerlinNoise.hpp"
#include "generator/Noise/PostProcessor.hpp"
class HeightMapBuilder {
private:
  HeightMapContainer &heightMapContainer;
  FractalBrownianMotion fractalBrownianMotion;
  PerlinNoise perlinNoise;
  PostProcessor postProcessor;
  TerrainConfig terrainConfig;

public:
  void heightMapBuilder();
  HeightMapBuilder(HeightMapContainer &heightMapContainer,
                   FractalBrownianMotion fractalBrownianMotion,
                   PerlinNoise perlinNoise, PostProcessor postProcessor,
                   TerrainConfig terrainConfig)
      : heightMapContainer(heightMapContainer),
        fractalBrownianMotion(fractalBrownianMotion), perlinNoise(perlinNoise),
        postProcessor(postProcessor), terrainConfig(terrainConfig) {};
};