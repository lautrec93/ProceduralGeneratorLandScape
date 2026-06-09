#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "app/Application.hpp"
#include "generator/IOConfigs/GuiInput.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "generator/TerrainSystem.hpp"
#include "glm/detail/type_mat.hpp"
#include "render/Camera.hpp"
#include "render/Shader.hpp"

#include "stb_image.h"
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <future>
#include <iostream>
#include <ostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned loadTexture(const char *path, bool sRGB);
unsigned int loadCubemap(const char *path);

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

Camera camera(glm::vec3(2000.0f, 3000.0f, 8000.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int Application::runApplication(Mesh &mesh) {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TerrainGen", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_FRAMEBUFFER_SRGB);

  Shader terrainShader(ASSETS_DIR "/shaders/terrain.vert",
                       ASSETS_DIR "/shaders/terrain.frag");

  Shader skyBoxShader(ASSETS_DIR "/shaders/skybox.vert",
                      ASSETS_DIR "/shaders/skybox.frag");

  float skyboxVertices[] = {
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * mesh.vertices.size(),
               mesh.vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices) * mesh.indices.size(),
               mesh.indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)offsetof(Vertices, coord));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, normal)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, uv)));
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, colour)));
  glEnableVertexAttribArray(3);

  unsigned int skyboxVAO, skyboxVBO;
  glGenVertexArrays(1, &skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glBindVertexArray(skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  unsigned int cubemapTexture =
      loadCubemap(ASSETS_DIR "/textures/StandardCubeMap 4.png");

  unsigned int grassTex = loadTexture(ASSETS_DIR "/textures/field-7.jpg", true);
  unsigned int rockTex = loadTexture(ASSETS_DIR "/textures/rocks-10.jpg", true);
  unsigned int sandTex = loadTexture(
      ASSETS_DIR
      "/textures/aerial_beach_01_4k/textures/aerial_beach_01_diff_4k.jpg",
      true);
  unsigned int snowTex = loadTexture(ASSETS_DIR "/textures/snow-1.jpg", true);
  unsigned int swampTex =
      loadTexture(ASSETS_DIR "/textures/close-up-forest-moss-cliff.jpg", true);

  terrainShader.use();
  terrainShader.setInt("material.diffuse", 0.0);
  terrainShader.setInt("grassTex", 0);
  terrainShader.setInt("rockTex", 1);
  terrainShader.setInt("snowTex", 2);
  terrainShader.setInt("sandTex", 3);
  terrainShader.setInt("swampTex", 4);

  skyBoxShader.use();
  skyBoxShader.setInt("skybox", 0);

  enum class AppState { MENU, LOADING, RENDERING };
  AppState state = AppState::MENU;
  GuiInput gui;
  std::atomic<float> progress{0.0f};
  std::future<void> genFuture;

  while (!glfwWindowShouldClose(window)) {
    glDisable(GL_CULL_FACE);
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    int winW, winH;
    glfwGetWindowSize(window, &winW, &winH);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (state == AppState::MENU) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ImVec2 menuSize = {440, 620};
      ImGui::SetNextWindowPos(
          {(winW - menuSize.x) / 2.0f, (winH - menuSize.y) / 2.0f},
          ImGuiCond_Always);
      ImGui::SetNextWindowSize(menuSize, ImGuiCond_Always);

      if (gui.drawMenu()) {
        auto config = gui.buildConfig();
        progress = 0.0f;
        genFuture =
            std::async(std::launch::async, [&mesh, config, &progress]() {
              TerrainSystem ts;
              ts.runTerrainSystem(config, mesh, progress);
              progress = 1.0f;
            });
        state = AppState::LOADING;
      }

    } else if (state == AppState::LOADING) {
      glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ImVec2 loadSize = {400, 80};
      ImGui::SetNextWindowPos(
          {(winW - loadSize.x) / 2.0f, (winH - loadSize.y) / 2.0f},
          ImGuiCond_Always);
      ImGui::SetNextWindowSize(loadSize, ImGuiCond_Always);
      ImGui::Begin("##loading", nullptr,
                   ImGuiWindowFlags_NoDecoration |
                       ImGuiWindowFlags_NoBackground);
      ImGui::Text("Generating terrain...");
      ImGui::ProgressBar(progress.load(), {380, 30});
      ImGui::End();

      if (genFuture.valid() && genFuture.wait_for(std::chrono::seconds(0)) ==
                                   std::future_status::ready) {
        genFuture.get();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * mesh.vertices.size(),
                     mesh.vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(Indices) * mesh.indices.size(), mesh.indices.data(),
                     GL_STATIC_DRAW);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstMouse = true;
        state = AppState::RENDERING;
      }

    } else {

      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        state = AppState::MENU;
        firstMouse = true;
      } else {
        processInput(window);

        glClearColor(0.04f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grassTex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, rockTex);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, snowTex);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, sandTex);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, swampTex);

        terrainShader.use();
        terrainShader.setVec3("light.direction", -0.1f, -1.0f, -0.1f);
        terrainShader.setVec3("viewPos", camera.Position);

        terrainShader.setVec3("light.ambient", 0.073f, 0.073f, 0.047f);
        terrainShader.setVec3("light.diffuse", 0.610f, 0.533f, 0.318f);
        terrainShader.setVec3("light.specular", 0.218f, 0.218f, 0.218f);

        terrainShader.setVec3("material.specular", 0.05f, 0.07f, 0.03f);
        terrainShader.setFloat("material.shininess", 4.0f);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
            10.0f, 50000.0f);
        glm::mat4 view = camera.camera_view();

        terrainShader.setMat4("projection", projection);
        terrainShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        terrainShader.setMat4("model", model);

        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
        terrainShader.setMat3("normalMatrix", normalMatrix);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices.size() * 3, GL_UNSIGNED_INT,
                       0);

        glDepthFunc(GL_LEQUAL);
        skyBoxShader.use();
        view = glm::mat4(glm::mat3(camera.camera_view()));
        skyBoxShader.setMat4("view", view);
        skyBoxShader.setMat4("projection", projection);

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
      }
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDisable(GL_DEPTH_TEST);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &skyboxVAO);
  glDeleteBuffers(1, &skyboxVBO);

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window) {
  float cameraSpeed = 2000.0f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::RIGHT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera::Camera_Movement::UP, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const *path, bool sRGB = false) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    GLenum internalFormat;

    if (nrComponents == 1) {
      format = GL_RED;
      internalFormat = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
      internalFormat = sRGB ? GL_SRGB : GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
      internalFormat = sRGB ? GL_SRGB_ALPHA : GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

unsigned int loadCubemap(const char *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  stbi_set_flip_vertically_on_load(false);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  if (!data) {
    std::cout << "Cross cubemap failed to load: " << path << std::endl;
    return textureID;
  }

  int faceW = width / 4;
  int faceH = height / 3;

  struct FaceLoc {
    int col, row;
  };
  FaceLoc faces[6] = {
      {2, 1}, {0, 1}, {1, 0}, {1, 2}, {1, 1}, {3, 1},
  };

  GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
  GLenum internalFormat = (nrChannels == 4) ? GL_SRGB_ALPHA : GL_SRGB;

  std::vector<unsigned char> faceData(faceW * faceH * nrChannels);

  for (int i = 0; i < 6; i++) {
    int xOff = faces[i].col * faceW;
    int yOff = faces[i].row * faceH;

    for (int y = 0; y < faceH; y++) {
      unsigned char *srcRow =
          data + ((size_t)(yOff + y) * width + xOff) * nrChannels;
      unsigned char *dstRow =
          faceData.data() + (size_t)(y * faceW) * nrChannels;
      std::memcpy(dstRow, srcRow, (size_t)faceW * nrChannels);
    }

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, faceW,
                 faceH, 0, format, GL_UNSIGNED_BYTE, faceData.data());
  }

  stbi_image_free(data);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}
