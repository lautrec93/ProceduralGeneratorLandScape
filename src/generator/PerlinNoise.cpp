#define XXH_INLINE_ALL
#include "PerlinNoise.hpp"
#include "Offsets.hpp"
#include "xxhash.h"
#include <vector>

void PerlinNoise::noise(unsigned nodes) {
  auto &field = heightMap_pn.getFieldXY();
  unsigned i{0};
  unsigned j{0};
  for (i; i < field.size(); i++) {
    for (j; j < field[0].size(); j++) {
      double x = i * scaleXY;
      double y = j * scaleXY;
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

      unsigned hash00 =
          XXH3_64bits(node00.data(), node00.size() * sizeof(Offsets));
      unsigned hash10 =
          XXH3_64bits(node10.data(), node10.size() * sizeof(Offsets));
      unsigned hash01 =
          XXH3_64bits(node01.data(), node01.size() * sizeof(Offsets));
      unsigned hash11 =
          XXH3_64bits(node11.data(), node11.size() * sizeof(Offsets));

      unsigned index00 = hash00 & 7; // lenght of array offsets is 8
      unsigned index10 = hash10 & 7;
      unsigned index01 = hash01 & 7;
      unsigned index11 = hash11 & 7;

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

      double fadeU = 6 * std::pow(ptlocX, 5) -
                     15 * std::pow(ptlocX, 4) * std::pow(ptlocX, 3);
      double fadeV = 6 * std::pow(ptlocY, 5) -
                     15 * std::pow(ptlocY, 4) * std::pow(ptlocY, 3);

      double interpx0 = dot00 + fadeU * (dot10 - dot00);
      double interpx1 = dot01 + fadeU * (dot11 - dot01);

      heightMap_pn.getFieldXY()[i][j] =
          interpx0 + fadeV * (interpx1 - interpx0);
    }
  }
}
