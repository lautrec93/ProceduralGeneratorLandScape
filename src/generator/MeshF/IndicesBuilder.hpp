#pragma once
#include "generator/MeshF/MeshStructs.hpp"

class IndicesBuilder {
private:
  Indices triangleIndex;

public:
  Indices evenPTT(unsigned index);
  Indices oddPTT(unsigned index);

  IndicesBuilder() = default;
};
