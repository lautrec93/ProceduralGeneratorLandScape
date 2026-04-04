#include "generator/FractalBrownianMotion.hpp"
#include "generator/Globals.hpp"
#include "generator/HeightMapContainer.hpp"
#include "generator/HeightMapGenerator.hpp"
#include "generator/Input.hpp"
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshBuilder.hpp"
#include "generator/MeshF/NormalBuilder.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include "generator/NoiseParametres.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/PostProcessor.hpp"
#include "generator/SaveJSON.hpp"
#include "generator/TerrainConfig.hpp"
#include <cctype>
#include <string>
#include <vector>
int example();
int main() {

  Input input;
  auto inputValues = input.startInput();

  NUMBER_OF_NODES_IN_LINE = inputValues[0].size / inputValues[0].cellSize;

  HeightMapGenerator heightMainMapGenerator{inputValues[0]};
  HeightMapContainer heightMapMainContainer{
      heightMainMapGenerator.fieldXYCreator(NUMBER_OF_NODES_IN_LINE)};

  NoiseParametres perlinNoiseParam{heightMapMainContainer.getHeightMap(),
                                   inputValues[0]};

  PerlinNoise perlinNoise;

  FractalBrownianMotion fBM{heightMapMainContainer, inputValues[0]};
  fBM.fractalBrownianMotion(perlinNoise);

  PostProcessor postProc{heightMapMainContainer};
  postProc.normalizeFunction();
  postProc.remapFunction(inputValues[0].coefficient);
  postProc.scalingFunction(inputValues[0].minHeight, inputValues[0].maxHeight);
  // heightMapMainContainer.showMap();
  heightMapMainContainer.showMin();
  heightMapMainContainer.showMax();
  heightMapMainContainer.showMid(std::pow(NUMBER_OF_NODES_IN_LINE, 2));
  saveJSON(heightMapMainContainer.getHeightMap(), "heightmap.json");
  CoordsBuilder coordsBuilder(heightMapMainContainer, inputValues[0]);
  Mesh mesh;
  NeighbouredTrianglesFinder nTF(mesh, inputValues[0]);
  SingleAngleNormalHandler sANH;
  NormalBuilder normalBuilder(mesh, inputValues[0], coordsBuilder, nTF, sANH);
  UVBuilder uvBuilder(inputValues[0]);
  VerticesBuilder verticesBuilder(coordsBuilder, normalBuilder, uvBuilder);
  MeshBuilder meshBuilder(mesh, verticesBuilder);
  meshBuilder.meshBuild();
}