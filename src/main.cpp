#include "app/Application.hpp"
#include "generator/TerrainSystem.hpp"
#include <iostream>

int main() {
  Mesh mesh;

  TerrainSystem terrainSystem;
  terrainSystem.runTerrainSystem(mesh);
  /*for (unsigned i{0}; i < 100; i++) {
    std::cout << mesh.indices[i].a << " " << mesh.indices[i].b << " "
              << mesh.indices[i].a << std::endl;
  }
  for (unsigned i{0}; i < 100; i++) {
    std::cout << mesh.vertices[i].coord.x << " " << mesh.vertices[i].coord.y
              << " " << mesh.vertices[i].coord.z << std::endl;
  }*/
  Application application;
  application.runApplication(mesh);
  /*for (unsigned i{0}; i < 100; i++) {
    std::cout << mesh.indices[i].a << " " << mesh.indices[i].b << " "
              << mesh.indices[i].a << std::endl;
  }
  for (unsigned i{0}; i < 100; i++) {
    std::cout << mesh.vertices[i].coord.x << " " << mesh.vertices[i].coord.y
              << " " << mesh.vertices[i].coord.z << std::endl;
  }*/
}
