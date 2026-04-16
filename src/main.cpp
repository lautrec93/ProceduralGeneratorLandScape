#include "glad/glad.h"

#include "GLFW/glfw3.h"
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
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(1920, 1080, "TerrainGen", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create the window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to connect GLAD" << std::endl;
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  /*Input input;
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
  Mesh mesh;
  SingleAngleNormalHandler sANH;
  NormalBuilder normalBuilder(mesh, coordsBuilder, sANH);
  UVBuilder uvBuilder(inputValues[0]);
  ColourBuilder colourBuilder(perlinNoise);
  VerticesBuilder verticesBuilder(inputValues[0], coordsBuilder, normalBuilder,
                                  uvBuilder, colourBuilder);
  MeshBuilder meshBuilder(mesh, verticesBuilder);
  meshBuilder.meshBuild();*/
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}