#pragma once
#include "generator/MeshF/CoordsBuilder.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include "generator/MeshF/SingleAngleNormalHandler.hpp"
#include <range/v3/view/any_view.hpp>
#include <range/v3/view/concat.hpp>

class NormalBuilder {
private:
  CoordsBuilder coordBuilder;
  SingleAngleNormalHandler &sANH;
  Mesh &mesh;
  Normal normalProcessing(const Indices &triangle);
  ranges::any_view<Indices> windowOption(unsigned size, unsigned index,
                                         std::vector<Indices> &indices);

public:
  Normal normalSummation(unsigned index);

  NormalBuilder(Mesh &mesh, CoordsBuilder coordBuilder,
                SingleAngleNormalHandler &sANH)
      : mesh(mesh), coordBuilder(coordBuilder), sANH(sANH) {};
};