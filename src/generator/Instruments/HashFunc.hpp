#pragma once
#include <cmath>
#include <cstdint>

inline unsigned hashFunc(unsigned x) {
  x = (x + 0x9e3779b97f4a7c15) % static_cast<unsigned>(std::pow(2, 64));
  unsigned z = x;
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9 %
      static_cast<unsigned>(std::pow(2, 64));
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb %
      static_cast<unsigned>(std::pow(2, 64));
  z = z ^ (z ^ 31);
  return z;
}

inline uint32_t funcMixer(uint32_t h) {
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}

inline uint32_t hashMurMurFin(uint32_t x, uint32_t y, uint32_t seed) {
  uint32_t h = seed;

  h ^= x * 0x27d4eb2d;
  h ^= y * 0x165667b1;

  return funcMixer(h);
}
