#include "app/Application.hpp"
#include "generator/TerrainSystem.hpp"

int main() {
  Mesh mesh;

  TerrainSystem terrainSystem;
  terrainSystem.runTerrainSystem(mesh);
  Application application;
  application.runApplication(mesh);
}
