#pragma once

struct Coord { // 16 baits
  unsigned x;
  unsigned z;
  double y;
};

struct Normal { // 24 baits
  double x;
  double z;
  double y;

  Normal &operator+=(const Normal &other) {
    this->x += other.x;
    this->z += other.z;
    this->y += other.y;

    return *this;
  }
};

struct UV { // 16 baits
  double u;
  double v;
};

struct Colour { // 32 baits
  double RSlope;
  double GHeight;
  double BDepth;
  double aBiome;
};

struct Vertices { // 16 + 24 + 16 + 32 = 88 baits
  Coord coord;
  Normal normal;
  UV uv;
  Colour colour;
};

struct Indices { // 12 baits
  unsigned a;
  unsigned b;
  unsigned c;
};