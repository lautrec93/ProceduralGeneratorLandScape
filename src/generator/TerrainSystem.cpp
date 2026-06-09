#include "generator/TerrainSystem.hpp"
#include "generator/HeightMap/HeightMapBuilder.hpp"
#include "generator/HeightMap/HeightMapContainer.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshBuilder.hpp"
#include "generator/MeshF/NormalBuilder.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/Noise/FractalBrownianMotion.hpp"
#include "generator/Noise/PerlinNoise.hpp"
#include "generator/Noise/PostProcessor.hpp"
#include <cctype>

void TerrainSystem::runTerrainSystem(const TerrainConfig &config, Mesh &mesh,
                                     std::atomic<float> &progress) {

  progress = 0.05f;
  NUMBER_OF_NODES_IN_LINE = config.size / config.cellSize;
  HeightMapContainer heightMapMainContainer;
  PerlinNoise perlinNoise(config);
  FractalBrownianMotion fractalBrownianMotion(perlinNoise);
  PostProcessor postProcessor(heightMapMainContainer);
  HeightMapBuilder heightMapMainBuilder(heightMapMainContainer,
                                        fractalBrownianMotion, perlinNoise,
                                        postProcessor, config);

  progress = 0.15f;

  heightMapMainBuilder.heightMapBuilder();
  progress = 0.65f;

  CoordsBuilder coordsBuilder(heightMapMainContainer, config);
  SingleAngleNormalHandler sANH;
  NormalBuilder normalBuilder(mesh, coordsBuilder, sANH);
  UVBuilder uvBuilder(config);
  ColourBuilder colourBuilder(perlinNoise);
  progress = 0.87f;

  VerticesBuilder verticesBuilder(config, coordsBuilder, normalBuilder,
                                  uvBuilder, colourBuilder);
  progress = 0.93f;

  MeshBuilder meshBuilder(mesh, verticesBuilder);
  meshBuilder.meshBuild();
  progress = 1.0f;
}