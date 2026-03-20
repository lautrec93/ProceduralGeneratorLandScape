#include "generator/FractalBrownianMotion.hpp"
#include "generator/HeightMapFinContainer.hpp"
#include "generator/HeightMapGenerator.hpp"
#include "generator/HeightMapRawContainer.hpp"
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
  double coefficient = 2.5;

  HeightMapGenerator heightMainMapGenerator{inputValues[0]};

  heightMainMapGenerator.fieldXYCreator(nodes);

  NoiseParametres perlinNoiseParam{heightMainMapGenerator.getFieldXY(),
                                   inputValues[0]};

  PerlinNoise perlinNoise{0.05f, heightMainMapGenerator};

  FractalBrownianMotion fBM{heightMainMapGenerator, inputValues[0]};
  auto finalHMap = fBM.fractalBrownianMotion(perlinNoise);

  HeightMapRawContainer<std::vector<std::vector<double>>> rawContainer(
      finalHMap);
  HeightMapFinContainer<std::vector<std::vector<double>>> finContainer(
      rawContainer.getValue());
  PostProcessor postProc{finContainer};
  postProc.normalizeFunction();
  postProc.remapFunction(coefficient);
  postProc.scalingFunction(inputValues[0].minHeight, inputValues[0].maxHeight);
  finContainer.showRawMap();
  finContainer.showMin();
  finContainer.showMax();
  finContainer.showMid(std::pow(nodes, 2));
  saveJSON(finContainer.getValue(), "heightmap.json");
}