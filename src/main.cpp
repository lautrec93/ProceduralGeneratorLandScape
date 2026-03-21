#include "generator/FractalBrownianMotion.hpp"
#include "generator/HeightMapContainer.hpp"
#include "generator/HeightMapGenerator.hpp"
#include "generator/Input.hpp"
#include "generator/NoiseParametres.hpp"
#include "generator/PerlinNoise.hpp"
#include "generator/PostProcessor.hpp"
#include "generator/SaveJSON.hpp"
#include <cctype>
#include <string>
#include <vector>
int main() {

  Input input;
  auto inputValues = input.startInput();

  unsigned nodes = inputValues[0].size / inputValues[0].cellSize;

  HeightMapGenerator heightMainMapGenerator{inputValues[0]};
  HeightMapContainer heightMapMainContainer{
      heightMainMapGenerator.fieldXYCreator(nodes)};

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
  heightMapMainContainer.showMid(std::pow(nodes, 2));
  saveJSON(heightMapMainContainer.getHeightMap(), "heightmap.json");
}