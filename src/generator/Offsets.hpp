#pragma once
#include <array>

struct Offsets {
  double x{0};
  double y{0};
};

constexpr std::array<Offsets, 8> offsets = {
    {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}};
