#define XXH_INLINE_ALL
#include "GuiInput.hpp"
#include "generator/Instruments/xxhash.h"
#include <algorithm>
#include <imgui.h>
#include <string>

bool GuiInput::drawMenu() {
  ImGui::SetNextWindowPos({50, 50}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({420, 560}, ImGuiCond_Once);
  ImGui::Begin("Terrain Parameters");

  ImGui::InputInt("Field size", &size);
  ImGui::InputFloat("Cell size", &cellSize);
  ImGui::InputFloat("Noise scale", &noizeScale);
  ImGui::InputFloat("Amplitude", &baseAmplitude);
  ImGui::InputFloat("Frequency", &baseFrequency);
  ImGui::InputFloat("Lacunarity", &lacunarity);
  ImGui::InputFloat("Persistence", &persistence);
  ImGui::InputFloat("Coefficient", &coefficient);
  ImGui::InputInt("Octaves", &octaveNumber);
  ImGui::InputFloat("Min height", &minHeight);
  ImGui::InputFloat("Max height", &maxHeight);
  ImGui::InputFloat("Sea level", &seaLevel);
  ImGui::InputText("Seed", seedInput, sizeof(seedInput));

  ImGui::Spacing();
  bool clicked = ImGui::Button("Generate", {200, 40});
  ImGui::End();
  return clicked;
}

TerrainConfig GuiInput::buildConfig() {
  std::string s(seedInput);
  uint32_t seed;
  bool isNum = !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
  if (isNum) {
    seed = static_cast<uint32_t>(std::stoull(s));
  } else {
    auto h = XXH3_64bits(s.data(), s.size());
    seed = static_cast<uint32_t>(h ^ (h >> 32));
  }
  return TerrainConfig(seed, size, cellSize, noizeScale, baseAmplitude,
                       baseFrequency, coefficient, octaveNumber, lacunarity,
                       persistence, maxHeight, minHeight, seaLevel);
}