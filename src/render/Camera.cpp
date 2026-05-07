#include "glad/glad.h"

#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "glm/glm/detail/func_matrix.hpp"
#include "glm/glm/detail/func_trigonometric.hpp"
#include "glm/glm/detail/type_mat.hpp"
#include "glm/glm/detail/type_vec.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

glm::mat4 Camera::camera_view() {
  return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = MovementSpeed * deltaTime;
  if (direction == Camera_Movement::FORWARD)
    Position += Front * velocity;
  if (direction == Camera_Movement::BACKWARD)
    Position -= Front * velocity;
  if (direction == Camera_Movement::LEFT)
    Position -= Right * velocity;
  if (direction == Camera_Movement::RIGHT)
    Position += Right * velocity;
  if (direction == Camera_Movement::DOWN)
    Position -= Up * velocity;
  if (direction == Camera_Movement::UP)
    Position += Up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  if (Zoom >= 1.0f && Zoom <= 45.0f)
    Zoom -= yoffset;
  if (Zoom <= 1.0f)
    Zoom = 1.0f;
  if (Zoom >= 45.0f)
    Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}