#include "generator/TerrainSystem.hpp"
#include "generator/HeightMap/HeightMapBuilder.hpp"
#include "generator/HeightMap/HeightMapContainer.hpp"
#include "generator/IOConfigs/Input.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/Instruments/Globals.hpp"
#include "generator/Instruments/SaveJSON.hpp"
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshBuilder.hpp"
#include "generator/MeshF/NormalBuilder.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/Noise/FractalBrownianMotion.hpp"
#include "generator/Noise/PerlinNoise.hpp"
#include "generator/Noise/PostProcessor.hpp"
#include <cctype>
#include <string>
#include <vector>

void TerrainSystem::runTerrainSystem(Mesh &mesh) {
  Input input;
  auto inputValues = input.startInput();

  NUMBER_OF_NODES_IN_LINE = inputValues[0].size / inputValues[0].cellSize;
  HeightMapContainer heightMapMainContainer;
  PerlinNoise perlinNoise(inputValues[0]);
  FractalBrownianMotion fractalBrownianMotion(perlinNoise);
  PostProcessor postProcessor(heightMapMainContainer);
  HeightMapBuilder heightMapMainBuilder(heightMapMainContainer,
                                        fractalBrownianMotion, perlinNoise,
                                        postProcessor, inputValues[0]);
  heightMapMainBuilder.heightMapBuilder();

  // heightMapMainContainer.showMap();
  heightMapMainContainer.showMid();
  saveJSON(heightMapMainContainer.getHeightMap(), "heightmap.json");

  CoordsBuilder coordsBuilder(heightMapMainContainer, inputValues[0]);
  SingleAngleNormalHandler sANH;
  NormalBuilder normalBuilder(mesh, coordsBuilder, sANH);
  UVBuilder uvBuilder(inputValues[0]);
  ColourBuilder colourBuilder(perlinNoise);
  VerticesBuilder verticesBuilder(inputValues[0], coordsBuilder, normalBuilder,
                                  uvBuilder, colourBuilder);
  MeshBuilder meshBuilder(mesh, verticesBuilder);
  meshBuilder.meshBuild();
}