#pragma once
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/MeshF/Mesh.hpp"
#include <atomic>
class TerrainSystem {
public:
  void runTerrainSystem(Mesh &mesh);
  void runTerrainSystem(const TerrainConfig &config, Mesh &mesh,
                        std::atomic<float> &progress);
  TerrainSystem() = default;
};