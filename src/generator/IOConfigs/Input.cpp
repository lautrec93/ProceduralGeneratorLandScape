#define XXH_INLINE_ALL
#include "Input.hpp"
#include "generator/IOConfigs/TerrainConfig.hpp"
#include "generator/Instruments/xxhash.h"
#include <algorithm>
#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

std::vector<TerrainConfig> Input::startInput() {

  std::random_device rnd;
  std::mt19937 gen(rnd());
  std::uniform_int_distribution<> limits(100000000, 999999999);
  primarySeed = limits(gen);

  std::cout << "Enter field size \n";
  std::cin >> size;

  std::cout << "Enter cell size \n";
  std::cin >> cellSize;

  std::cout << "Enter noizeScale \n";
  std::cin >> noizeScale;

  std::cout << "Enter basical amplitude \n";
  std::cin >> baseAmplitude;

  std::cout << "Enter basical frequency \n";
  std::cin >> baseFrequency;

  std::cout << "Enter lacunarity \n";
  std::cin >> lacunarity;

  std::cout << "Enter persistence \n";
  std::cin >> persistence;

  std::cout << "Enter coefficient \n";
  std::cin >> coefficient;

  std::cout << "Enter number of octaves \n";
  std::cin >> octaveNumber;

  std::cout << "Enter minimal height \n";
  std::cin >> minHeight;

  std::cout << "Enter maximal height\n";
  std::cin >> maxHeight;

  std::cout << "Enter sea level \n";
  std::cin >> seaLevel;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Enter seed \n";
  std::getline(std::cin, primarySeed);

  if (ifSeedNum(primarySeed)) {
    seed = static_cast<uint32_t>(std::stoull(primarySeed));

  } else {
    auto processedSeed = XXH3_64bits(primarySeed.data(), primarySeed.size());
    seed = static_cast<uint32_t>(processedSeed ^ (processedSeed >> 32));
  }

  std::vector<TerrainConfig> finalInput{};
  finalInput.emplace_back(seed, size, cellSize, noizeScale, baseAmplitude,
                          baseFrequency, coefficient, octaveNumber, lacunarity,
                          persistence, maxHeight, minHeight, seaLevel);

  return finalInput;
}

bool Input::ifSeedNum(std::string &primarySeed) {
  return !primarySeed.empty() &&
         std::all_of(primarySeed.begin(), primarySeed.end(), ::isdigit);
}