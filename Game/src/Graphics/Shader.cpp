//
// Created by Dmitry Morozov on 30/3/23.
//

#include "Graphics/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::unordered_map<std::string, Shader> Shader::Shaders_;

void Shader::LoadShader(const char *name, const char *vertFile, const char *fragFile) {
  std::string vertCode, fragCode;
  try {
	std::ifstream vertexFile(vertFile);
	std::ifstream fragmentFile(fragFile);
	std::stringstream vShaderStream, fShaderStream;
	vShaderStream << vertexFile.rdbuf();
	fShaderStream << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();

	vertCode = vShaderStream.str();
	fragCode = fShaderStream.str();
  }
  catch (std::exception &e) {
	std::cout << "Load Shader Failed ! " << std::endl;
  }

  Shader shader;
  shader.Compile(vertCode.c_str(), fragCode.c_str());
  Shaders_[name] = shader;
}

Shader &Shader::GetShader(const char *name) {
  return Shader::Shaders_[name];
}

void Shader::Bind() const {
  glUseProgram(m_Id);
}

void Shader::UnBind() {
  glUseProgram(0);
}

void Shader::SetInt(const char *name, int value) {
  glUniform1i(GetUniformCache(name), value);
}

void Shader::SetInt(const char *name, int count, int *value) {
  glUniform1iv(GetUniformCache(name), count, value);
}

void Shader::SetFloat(const char *name, float value) {
  glUniform1f(GetUniformCache(name), value);
}

void Shader::SetVector2(const char *name, glm::vec2 value) {
  glUniform2f(GetUniformCache(name), value.x, value.y);
}

void Shader::SetVector3(const char *name, glm::vec3 value) {
  glUniform3f(GetUniformCache(name), value.x, value.y, value.z);
}

void Shader::SetVector4(const char *name, glm::vec4 value) {
  glUniform4f(GetUniformCache(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, glm::mat4 value) {
  glUniformMatrix4fv(GetUniformCache(name), 1, false, glm::value_ptr(value));
}

void Shader::Compile(const char *vertexCode, const char *fragmentCode) {
  unsigned int sVertex, sFragment;

  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexCode, nullptr);
  glCompileShader(sVertex);
  CheckCompileError(sVertex, "VERTEX");

  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentCode, nullptr);
  glCompileShader(sFragment);
  CheckCompileError(sFragment, "FRAGMENT");

  this->m_Id = glCreateProgram();
  glAttachShader(this->m_Id, sVertex);
  glAttachShader(this->m_Id, sFragment);
  glLinkProgram(this->m_Id);
  CheckCompileError(this->m_Id, "PROGRAM");

  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

unsigned int Shader::GetUniformCache(const std::string &name) {
  if (uniformCache.find(name)==uniformCache.end())
	return uniformCache[name];
  unsigned int location = glGetUniformLocation(m_Id, name.c_str());
  uniformCache[name] = location;
  return location;
}

void Shader::CheckCompileError(unsigned int object, const std::string &type) {
  int success;
  char infoLog[1024];
  if (type=="PROGRAM") {
	glGetProgramiv(object, GL_LINK_STATUS, &success);
	if (!success) {
	  glGetProgramInfoLog(object, 1024, nullptr, infoLog);
	  std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
	}
  } else {
	glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	if (!success) {
	  glGetShaderInfoLog(object, 1024, nullptr, infoLog);
	  std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
	}
  }
}

