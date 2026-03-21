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

      Offsets node00{cellX, cellY};
      Offsets node10{cellX + 1, cellY};
      Offsets node01{cellX, cellY + 1};
      Offsets node11{cellX + 1, cellY + 1};

      unsigned index00 =
          hashMurMurFin(node00.x, node00.y, params.terCon.seed) & 7;
      unsigned index10 =
          hashMurMurFin(node10.x, node10.y, params.terCon.seed) & 7;
      unsigned index01 =
          hashMurMurFin(node01.x, node01.y, params.terCon.seed) & 7;
      unsigned index11 =
          hashMurMurFin(node11.x, node11.y, params.terCon.seed) & 7;

      Offsets grad00{offsets[index00]};
      Offsets grad10{offsets[index10]};
      Offsets grad01{offsets[index01]};
      Offsets grad11{offsets[index11]};

      Offsets dir00{x - cellX, y - cellY};
      Offsets dir10{x - cellX - 1, y - cellY};
      Offsets dir01{x - cellX, y - cellY - 1};
      Offsets dir11{x - cellX - 1, y - cellY - 1};

      double dot00 = grad00.x * dir00.x + grad00.y * dir00.y;
      double dot10 = grad10.x * dir10.x + grad10.y * dir10.y;
      double dot01 = grad01.x * dir01.x + grad01.y * dir01.y;
      double dot11 = grad11.x * dir11.x + grad11.y * dir11.y;

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