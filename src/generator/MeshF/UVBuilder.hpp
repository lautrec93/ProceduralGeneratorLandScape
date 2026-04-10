#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/MeshF/MeshStructs.hpp"
class UVBuilder {
private:
  TerrainConfig terrainConfig;
  UV uv;

public:
  UV uvCounter(unsigned index);
  UVBuilder(TerrainConfig terrainConfig) : terrainConfig(terrainConfig) {};
};