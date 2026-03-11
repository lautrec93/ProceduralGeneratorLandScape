#pragma once

struct TerrainConfig {
  unsigned seed;
  unsigned size;
  float cellSize;

  float noizeScale;

  unsigned octaveNumber;
  float lacunarity;
  float persistence;

  float maxHeight;
  float minHeight;
  float seaLevel;
};