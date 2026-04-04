#include "generator/MeshF/MeshStructs.hpp"
#include "generator/TerrainConfig.hpp"
class UVBuilder {
private:
  TerrainConfig terrainConfig;
  UV uv;

public:
  UV uvCounter(unsigned index);
  UVBuilder(TerrainConfig terrainConfig) : terrainConfig(terrainConfig) {};
};