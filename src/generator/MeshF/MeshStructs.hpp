#pragma once

struct Coord {
  unsigned x;
  unsigned z;
  double y;
};

struct Normal {
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

struct UV {
  double u;
  double v;
};

struct Vertices {
  Coord coord;
  Normal normal;
  UV uv;
};

struct Indices {
  unsigned a;
  unsigned b;
  unsigned c;
};