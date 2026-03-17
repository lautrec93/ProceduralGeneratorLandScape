#include "PerlinNoise.hpp"
#include "HashFunc.hpp"
#include "NoiseParametres.hpp"
#include "Offsets.hpp"
#include "xxhash.h"
#include <vector>

void PerlinNoise::noise(const NoiseParametres &params) {
  unsigned i{0};
  unsigned j{0};
  for (auto row{params.field.begin()}; row != params.field.end(); ++row) {
    j = 0;
    for (auto col{row->begin()}; col != row->end(); ++col) {
      x = i * scaleXY * params.freq.value_or(1.0);
      y = j * scaleXY * params.freq.value_or(1.0);
      double cellX = std::floor(x);
      double cellY = std::floor(y);

      std::vector<Offsets> node00{};
      std::vector<Offsets> node01{};
      std::vector<Offsets> node10{};
      std::vector<Offsets> node11{};
      node00.push_back({cellX, cellY});
      node10.push_back({cellX + 1, cellY});
      node01.push_back({cellX, cellY + 1});
      node11.push_back({cellX + 1, cellY + 1});

      unsigned index00 =
          hashMurMurFin(node00[0].x, node00[0].y, params.terCon.seed) & 7;
      unsigned index10 =
          hashMurMurFin(node10[0].x, node10[0].y, params.terCon.seed) & 7;
      unsigned index01 =
          hashMurMurFin(node01[0].x, node01[0].y, params.terCon.seed) & 7;
      unsigned index11 =
          hashMurMurFin(node11[0].x, node11[0].y, params.terCon.seed) & 7;

      std::vector<Offsets> grad00{};
      std::vector<Offsets> grad01{};
      std::vector<Offsets> grad10{};
      std::vector<Offsets> grad11{};
      grad00.push_back(offsets[index00]);
      grad10.push_back(offsets[index10]);
      grad01.push_back(offsets[index01]);
      grad11.push_back(offsets[index11]);

      std::vector<Offsets> dir00{};
      std::vector<Offsets> dir01{};
      std::vector<Offsets> dir10{};
      std::vector<Offsets> dir11{};
      dir00.push_back({x - cellX, y - cellY});
      dir10.push_back({x - cellX - 1, y - cellY});
      dir01.push_back({x - cellX, y - cellY - 1});
      dir11.push_back({x - cellX - 1, y - cellY - 1});

      double dot00 = grad00[0].x * dir00[0].x + grad00[0].y * dir00[0].y;
      double dot10 = grad10[0].x * dir10[0].x + grad10[0].y * dir10[0].y;
      double dot01 = grad01[0].x * dir01[0].x + grad01[0].y * dir01[0].y;
      double dot11 = grad11[0].x * dir11[0].x + grad11[0].y * dir11[0].y;

      double ptlocX = x - cellX;
      double ptlocY = y - cellY;

      double fadeU = 6 * std::pow(ptlocX, 5) - 15 * std::pow(ptlocX, 4) +
                     10 * std::pow(ptlocX, 3);
      double fadeV = 6 * std::pow(ptlocY, 5) - 15 * std::pow(ptlocY, 4) +
                     10 * std::pow(ptlocY, 3);

      double interpx0 = dot00 + fadeU * (dot10 - dot00);
      double interpx1 = dot01 + fadeU * (dot11 - dot01);
      value = interpx0 + fadeV * (interpx1 - interpx0);

      params.field[i][j] = value;
      ++j;
    }
    ++i;
  }
}

double PerlinNoise::getValue() const { return value; };
double PerlinNoise::getX() const { return x; };
double PerlinNoise::getY() const { return y; };

void PerlinNoise::changeX(double amp) { x *= amp; };
void PerlinNoise::changeY(double amp) { y *= amp; };