#pragma once
#include "generator/IOConfigs/TerrainConfig.hpp"
#include <string>

class GuiInput {
public:
  int size = 512;
  float cellSize = 1.0f;
  float noizeScale = 1.0f;
  float baseAmplitude = 50.0f;
  float baseFrequency = 1.0f;
  float lacunarity = 2.0f;
  float persistence = 0.5f;
  float coefficient = 1.0f;
  int octaveNumber = 6;
  float minHeight = 0.0f;
  float maxHeight = 100.0f;
  float seaLevel = 20.0f;
  char seedInput[256] = "myseed";

  bool ready = false;

  bool drawMenu();

  TerrainConfig buildConfig();
};