#pragma once

struct Coord {
  float x;
  float z;
  float y;
};

struct Normal {
  float x;
  float z;
  float y;

  Normal &operator+=(const Normal &other) {
    this->x += other.x;
    this->z += other.z;
    this->y += other.y;

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

struct Vertices {
  Coord coord;
  Normal normal;
  UV uv;
  Colour colour;
};

struct Indices {
  unsigned a;
  unsigned b;
  unsigned c;
};