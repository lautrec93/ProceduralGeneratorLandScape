#include <cmath>

unsigned hashFunc(unsigned x) {
  x = (x + 0x9e3779b97f4a7c15) % static_cast<unsigned>(std::pow(2, 64));
  unsigned z = x;
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9 %
      static_cast<unsigned>(std::pow(2, 64));
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb %
      static_cast<unsigned>(std::pow(2, 64));
  z = z ^ (z ^ 31);
  return z;
}

// not to forget at the end add bitcast for float/double arguments
// not to forhet about -0.0 and 0.0 dif

// for string should use xxhash