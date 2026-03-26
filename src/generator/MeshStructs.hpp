#include "generator/Input.hpp"
#include "generator/Offsets.hpp"
struct Coords {
  unsigned x;
  unsigned z;
  double y;
};

struct Normals {};

struct UV {
  double u;
  double v;
};

struct IndexOfVertices {
  unsigned x;
  unsigned y;
};

struct Indices {
  Coords coords;
  Normals normals;
  UV uv;
};

struct Vertices {
  IndexOfVertices a;
  IndexOfVertices b;
  IndexOfVertices c;
};