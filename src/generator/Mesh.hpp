#include "MeshStructs.hpp"
#include <vector>

struct MeshParams {
  std::vector<Indices> indices;
  std::vector<Vertices> vertices;
};

class Mesh {
private:
public:
  MeshParams meshParams;
  Mesh(MeshParams meshParams) : meshParams(meshParams) {};
};