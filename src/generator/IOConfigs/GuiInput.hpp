#pragma once
#include "generator/IOConfigs/TerrainConfig.hpp"

class GuiInput {
public:
  int size = 40000;
  float cellSize = 10.0f;
  float noizeScale = 0.05f;
  float baseAmplitude = 1.0f;
  float baseFrequency = 0.01f;
  float lacunarity = 2.0f;
  float persistence = 0.5f;
  float coefficient = 2.5f;
  int octaveNumber = 8;
  float minHeight = -1000.0f;
  float maxHeight = 4000.0f;
  float seaLevel = 5.0f;
  char seedInput[256] = "myseed";

  bool ready = false;

  bool drawMenu();

  TerrainConfig buildConfig();
};