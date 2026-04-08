#include "NormalBuilder.hpp"
#include "generator/Globals.hpp"
#include "generator/MeshF/MeshStructs.hpp"
#include <cmath>
#include <iostream>
#include <range/v3/view/concat.hpp>
#include <span>
#include <vector>

Normal NormalBuilder::normalSummation(
    unsigned index) { // тут мы принимаем индекс конкретной вершины, возвращаем
                      // нормаль для каждого ее треуголльника и суммируем их +
                      // нормализуем

  Normal finalNormal{};
  auto window = windowOption(mesh.indices.size(), index, mesh.indices);

  for (const auto &triangle : window) {
    finalNormal += (normalProcessing(triangle));
  }

  double normalLength = std::hypot(finalNormal.x, finalNormal.z, finalNormal.y);
  finalNormal = {finalNormal.x / normalLength, finalNormal.z / normalLength,
                 finalNormal.y / normalLength};
  return finalNormal;
}

Normal NormalBuilder::normalProcessing(
    const Indices &triangle) { // тут берем треугольник по адресу и для него
                               // считаем координаты, угол, нормаль и возвращаем
                               // отскейленную, готовую к суммированию нормаль
  Coord currentCoordA = coordBuilder.coordsCounting(triangle.a);
  Coord currentCoordB = coordBuilder.coordsCounting(triangle.b);
  Coord currentCoordC = coordBuilder.coordsCounting(triangle.c);
  double angle =
      sANH.angleCount(currentCoordB.x, currentCoordC.x, currentCoordA.x,
                      currentCoordB.z, currentCoordC.z, currentCoordA.z,
                      currentCoordB.y, currentCoordC.y, currentCoordA.y);
  Normal normal = sANH.singleNormalCounter(
      currentCoordB.x, currentCoordC.x, currentCoordA.x, currentCoordB.z,
      currentCoordC.z, currentCoordA.z, currentCoordB.y, currentCoordC.y,
      currentCoordA.y);
  Normal scaledNormal = {normal.x * angle, normal.z * angle, normal.y * angle};

  return scaledNormal;
}

ranges::any_view<Indices>
NormalBuilder::windowOption(unsigned size, unsigned index,
                            std::vector<Indices> &indices) {
  unsigned unix = 2 * NUMBER_OF_NODES_IN_LINE - 1;
  std::span<Indices> span1{};
  std::span<Indices> span2{};

  if (index == NUMBER_OF_NODES_IN_LINE - 1) {
    span1 = {&indices[unix - 2], 1};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if (size - index == NUMBER_OF_NODES_IN_LINE) {
    span1 = {
        &indices[2 * std::pow(NUMBER_OF_NODES_IN_LINE - 1, 2) - (unix - 1)], 1};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if (index < NUMBER_OF_NODES_IN_LINE &&
           (index % NUMBER_OF_NODES_IN_LINE < (NUMBER_OF_NODES_IN_LINE - 1) &&
            index % NUMBER_OF_NODES_IN_LINE > 0)) {
    span1 = {&indices[2 * index - 1], 3};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if (index > NUMBER_OF_NODES_IN_LINE - 1 &&
           index < (size - NUMBER_OF_NODES_IN_LINE) &&
           index % NUMBER_OF_NODES_IN_LINE == 0) {
    span1 = {&indices[(index / NUMBER_OF_NODES_IN_LINE - 1) * (unix - 1)], 1};
    span2 = {&indices[(index / NUMBER_OF_NODES_IN_LINE) * (unix - 1)], 2};
    return ranges::views::concat(span1, span2);
  }

  else if (index > NUMBER_OF_NODES_IN_LINE &&
           index < (size - NUMBER_OF_NODES_IN_LINE) &&
           index % NUMBER_OF_NODES_IN_LINE == (NUMBER_OF_NODES_IN_LINE - 1)) {
    span1 = {&indices[(index / NUMBER_OF_NODES_IN_LINE - 1) * (unix - 1) +
                      (unix - 3)],
             2};
    span2 = {&indices[(index / NUMBER_OF_NODES_IN_LINE + 1) * (unix - 1) - 1],
             1};
    return ranges::views::concat(span1, span2);
  }

  else if (index >= (size - NUMBER_OF_NODES_IN_LINE) &&
           (index % NUMBER_OF_NODES_IN_LINE < (NUMBER_OF_NODES_IN_LINE - 1) &&
            index % NUMBER_OF_NODES_IN_LINE > 0)) {

    span1 = {&indices[(index / NUMBER_OF_NODES_IN_LINE - 1) * (unix - 1) +
                      ((index % NUMBER_OF_NODES_IN_LINE - 1) * 2)],
             3};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if (index == 0) {
    span1 = {&indices[0], 2};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if (index == size - 1) {
    span1 = {&indices[2 * std::pow(NUMBER_OF_NODES_IN_LINE - 1, 2) - 1], 2};
    span2 = {};
    return ranges::views::concat(span1, span2);
  }

  else if ((index % NUMBER_OF_NODES_IN_LINE < (NUMBER_OF_NODES_IN_LINE - 1) &&
            index % NUMBER_OF_NODES_IN_LINE > 0) &&
           index > NUMBER_OF_NODES_IN_LINE &&
           index < (size - NUMBER_OF_NODES_IN_LINE)) {
    span1 = {&indices[(index / NUMBER_OF_NODES_IN_LINE - 1) * (unix - 1) +
                      ((index % NUMBER_OF_NODES_IN_LINE - 1) * 2)],
             3};
    span2 = {
        &indices[(index / NUMBER_OF_NODES_IN_LINE - 1) * (unix - 1) + unix], 3};
    return ranges::views::concat(span1, span2);
  } else {
    std::cout << index << "\n";
    throw std::runtime_error("Unexpected index in windowOption");
  }
}