#include "generator/Instruments/Globals.hpp"
#include <fstream>
#include <string>
#include <vector>

void saveJSON(const std::vector<double> &heightMap,
              const std::string &filename) {
  std::ofstream file(filename, std::ios::trunc);

  if (!file.is_open()) {
    return;
  }

  file << "[\n";

  for (size_t i{0}; i < heightMap.size(); ++i) {
    if (i % NUMBER_OF_NODES_IN_LINE == 0) {
      file << "[";
    }

    file << heightMap[i];

    if ((i % NUMBER_OF_NODES_IN_LINE) != NUMBER_OF_NODES_IN_LINE - 1) {
      file << ", ";
    } else {
      file << "]";
      if (i + 1 < heightMap.size()) {
        file << ",";
      }
      file << "\n";
    }
  }

  file << "]\n";
}