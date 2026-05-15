#pragma once

struct Coord {
  float x;
  float y;
  float z;
};

struct Normal {
  float x;
  float y;
  float z;

  Normal &operator+=(const Normal &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
  }
};

struct UV {
  float u;
  float v;
};

struct Colour {
  float RSlope;
  float GHeight;
  float BDepth;
  float aBiome;
};

struct Vertices { // 48
  Coord coord;    // 12
  Normal normal;  // 12
  UV uv;          // 8
  Colour colour;  // 16
};

struct Indices {
  unsigned a;
  unsigned b;
  unsigned c;
};