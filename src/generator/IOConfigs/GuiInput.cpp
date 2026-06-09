#define XXH_INLINE_ALL
#include "GuiInput.hpp"
#include "generator/Instruments/xxhash.h"
#include <algorithm>
#include <imgui.h>
#include <string>

bool GuiInput::drawMenu() {
  ImGui::Begin("Terrain Parameters", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  ImGui::InputInt("Field size", &size, 1);
  ImGui::InputFloat("Cell size", &cellSize, 1);
  ImGui::InputFloat("Noise scale", &noizeScale, 0.01f);
  ImGui::InputFloat("Amplitude", &baseAmplitude, 0.01f);
  ImGui::InputFloat("Frequency", &baseFrequency, 0.01f);
  ImGui::InputFloat("Lacunarity", &lacunarity, 0.01f);
  ImGui::InputFloat("Persistence", &persistence, 0.01f);
  ImGui::InputFloat("Coefficient", &coefficient, 0.01f);
  ImGui::InputInt("Octaves", &octaveNumber, 1);
  ImGui::InputFloat("Min height", &minHeight, 0.1f);
  ImGui::InputFloat("Max height", &maxHeight, 0.1f);
  ImGui::InputFloat("Sea level", &seaLevel, 0.1f);
  ImGui::InputText("Seed", seedInput, sizeof(seedInput));

  ImGui::Spacing();
  bool clicked = ImGui::Button("Generate", {380, 40});

  ImGui::Spacing();
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
  if (ImGui::Button("Exit", {380, 35})) {
    exit(0);
  }
  ImGui::PopStyleColor(2);

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