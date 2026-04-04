#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/MeshF/NormalBuilder.hpp"
#include "generator/MeshF/UVBuilder.hpp"
class VerticesBuilder {
private:
  Vertices vertex;
  CoordsBuilder coordBuilder;
  NormalBuilder normalBuilder;
  UVBuilder uvBuilder;

public:
  Vertices vertexBuild(unsigned index);
  VerticesBuilder(CoordsBuilder coordBuilder, NormalBuilder normalBuilder,
                  UVBuilder uvBuilder)
      : coordBuilder(coordBuilder), normalBuilder(normalBuilder),
        uvBuilder(uvBuilder) {};
};