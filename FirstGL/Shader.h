#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	//program ID
	GLuint ID;

	//constructor for building the shader program
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	
	//use the program
	void Use();
	void Delete();
	GLuint GetID() const; 

	//utilities for uniforms
	void SetBool(const std::string &name, const bool value) const;
	void SetFloat(const std::string& name, const float value) const;
	void SetInt(const std::string& name, const int value) const;
	void setMat4f(const std::string& name, const glm::mat4& matrix) const;
	void setVec2(const std::string& name, const glm::vec2& vec) const;
	void setVec3(const std::string& name, const glm::vec3& vec) const;
	void setVec4(const std::string& name, const glm::vec4& vec) const;
};

#endif
