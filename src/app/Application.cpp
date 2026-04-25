#include "generator/MeshF/MeshStructs.hpp"
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "app/Application.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "glm/glm/detail/func_matrix.hpp"
#include "glm/glm/detail/func_trigonometric.hpp"
#include "glm/glm/detail/type_mat.hpp"
#include "glm/glm/detail/type_vec.hpp"
#include "render/Shader.hpp"
#include "stb_image.h"
#include </Users/arsenikarokhin/VSCodeProjects/TerrainGen/external/glad/include/glm/glm/glm.hpp>
#include </Users/arsenikarokhin/VSCodeProjects/TerrainGen/external/glad/include/glm/glm/gtc/matrix_transform.hpp>
#include </Users/arsenikarokhin/VSCodeProjects/TerrainGen/external/glad/include/glm/glm/gtc/type_ptr.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Shader shader);

// Константы
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

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

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  Shader ourShader("/Users/arsenikarokhin/VSCodeProjects/TerrainGen/src/assets/"
                   "shaders/terrain.vert",
                   "/Users/arsenikarokhin/VSCodeProjects/TerrainGen/src/assets/"
                   "shaders/terrain.frag");

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

  // Атрибут позиции
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)offsetof(Vertices, coord));
  glEnableVertexAttribArray(0);

  // Атрибут нормали
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, normal)));
  glEnableVertexAttribArray(1);

  // Атрибут UV
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, uv)));
  glEnableVertexAttribArray(2);

  // Атрибут цвета/текстуры
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices),
                        (void *)(offsetof(Vertices, colour)));
  glEnableVertexAttribArray(3);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    processInput(window, ourShader);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::cout << mesh.vertices[(unsigned)glfwGetTime()].coord.x << " "
              << mesh.vertices[(unsigned)glfwGetTime()].coord.y << " "
              << mesh.vertices[(unsigned)glfwGetTime()].coord.z << std::endl;

    // glm::mat4 projection = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(3.0f, 3.0f, -3.0f));
    glm::mat4 model = glm::mat4(1.0f);
    // glm::mat4 view = glm::mat4(1.0f);

    float time = glfwGetTime(); // или SDL_GetTicks() / 1000.0f

    float orbitYaw = time * 30.0f; // 30 градусов в секунду, меняй под себя
    float orbitPitch =
        20.0f; // фиксированный наклон, или тоже можно анимировать
    float orbitRadius = 5000.0f;

    float yawRad = orbitYaw * (M_PI / 180.0f);
    float pitchRad = orbitPitch * (M_PI / 180.0f);

    glm::vec3 target = {2000.0f, 1500.0f, 2000.0f};
    glm::vec3 cameraPos;

    cameraPos.x = target.x + orbitRadius * cosf(pitchRad) * sinf(yawRad);
    cameraPos.y = target.y + orbitRadius * sinf(pitchRad);
    cameraPos.z = target.z + orbitRadius * cosf(pitchRad) * cosf(yawRad);

    glm::mat4 view = lookAt(cameraPos, target, (glm::vec3){0, 1, 0});

    /*glm::vec3 cameraPos =
            glm::vec3(-500.0f, 1500.0f, -3500.0f); // левее и дальше
    glm::vec3 cameraTarget =
        glm::vec3(1000.0f, 1500.0f, 1000.0f); // центр terrain
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);*/

    glm:: // near должен быть не слишком маленьким, far — перекрывать всю сцену
        mat4 projection = glm::perspective(
            glm::radians(45.0f), // fov
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            10.0f, // near — не ставь 0.001, при больших сценах будет z-fighting
            50000.0f // far — должен покрывать весь диапазон
        );
    // projection =
    //   glm::perspective(glm::radians(45.0f),
    //                  (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    ourShader.use();
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);
    ourShader.setMat4("model", model);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, mesh.indices.size() * 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDisable(GL_DEPTH_TEST);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window, Shader shader) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}