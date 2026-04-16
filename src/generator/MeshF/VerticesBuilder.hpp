#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/MeshF/ColourBuilder.hpp"
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/MeshF/NormalBuilder.hpp"
#include "generator/MeshF/UVBuilder.hpp"
class VerticesBuilder {
private:
  TerrainConfig terrainConfig;
  Vertices vertex;
  CoordsBuilder coordBuilder;
  NormalBuilder normalBuilder;
  UVBuilder uvBuilder;
  ColourBuilder colourBuilder;

public:
  Vertices vertexBuild(unsigned index);
  VerticesBuilder(TerrainConfig terrainConfig, CoordsBuilder coordBuilder,
                  NormalBuilder normalBuilder, UVBuilder uvBuilder,
                  ColourBuilder colourBuilder)
      : terrainConfig(terrainConfig), coordBuilder(coordBuilder),
        normalBuilder(normalBuilder), uvBuilder(uvBuilder),
        colourBuilder(colourBuilder) {};
};