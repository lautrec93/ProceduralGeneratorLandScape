#pragma once
#include "glm/glm/detail/type_mat.hpp"
#include <iostream>

class Shader {
private:
  void checkCompileError(unsigned shader, std::string type);

public:
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

  unsigned programID;
  void use();
  Shader(const char *vertexPath, const char *fragmentPath);
};