//
// Created by Dmitry Morozov on 30/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_SHADER_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_SHADER_HPP_

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <unordered_map>
namespace Graphics {

class Shader {
 public:
  static void LoadShader(const char *name, const char *vertFile, const char *fragFile);
  static Shader &GetShader(const char *name);
  static std::unordered_map<std::string, Shader> Shaders_;
 public:
  void Bind() const;
  static void UnBind();
  void Compile(const char *vertexCode, const char *fragmentCode);
  void SetInt(const char *name, int value);
  void SetInt(const char *name, int count, int *value);
  void SetFloat(const char *name, float value);
  void SetVector2(const char *name, glm::vec2 value);
  void SetVector3(const char *name, glm::vec3 value);
  void SetVector4(const char *name, glm::vec4 value);
  void SetMatrix4(const char *name, glm::mat4 value);

 private:
  unsigned int m_Id;
  std::unordered_map<std::string, unsigned int> uniformCache;
  static void CheckCompileError(unsigned int object, const std::string &type);
  unsigned int GetUniformCache(const std::string &name);
};

 } // namespace Graphics

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_SHADER_HPP_
