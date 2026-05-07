#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "app/Application.hpp"
#include "generator/MeshF/Mesh.hpp"
#include "glm/glm/detail/func_matrix.hpp"
#include "glm/glm/detail/func_trigonometric.hpp"
#include "glm/glm/detail/type_mat.hpp"
#include "glm/glm/detail/type_vec.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include <memory>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2000.0f;
const float ZOOM = 45.0f;
const float SENSITIVITY = 0.1f;

class Camera {
public:
  enum class Camera_Movement { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT };

  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  float Yaw;
  float Pitch;

  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
  }

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw = YAW, float pitch = PITCH)
      : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
  }

  glm::mat4 camera_view();

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);

  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);

  void ProcessMouseScroll(float yoffset);

private:
  void updateCameraVectors();
};