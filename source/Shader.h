#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
using namespace std;
using glm::vec3;	using glm::vec2;
using glm::mat4;	using glm::mat3;	using glm::mat2;
class Shader {
	static void CheckCompilerError(unsigned int shaderID);
	static void CheckLinkError(const char *programName, unsigned int programID);
	static void CompileShader(unsigned int &shaderID, string fileName, unsigned int SHADER_TYPE);
	static void LinkProgram(const char *programName, unsigned int &programID, unsigned int vertexShader, unsigned int fragmentShader);
	// more LinkProgram function overload will be add into newer version
public:
	Shader();
	Shader(string name, string shaderPath);
	// more shader constructor will be add into newer version
	void use();
	void checkUniformLocation(const char *name, unsigned int location);
	void setInt1(const char *name, int v1);
	void setInt2(const char *name, int v1, int v2);
	void setInt3(const char *name, int v1, int v2, int v3);
	void setInt4(const char *name, int v1, int v2, int v3, int v4);
	void setFloat1(const char *name, float v1);
	void setFloat2(const char *name, float v1, float v2);
	void setFloat3(const char *name, float v1, float v2, float v3);
	void setFloat4(const char *name, float v1, float v2, float v3, float v4);
	void setVec2(const char *name, vec2 vec);
	void setVec3(const char *name, vec3 vec);
	void setVec4(const char *name, vec3 vec);
	void setMat2(const char *name, mat2 mat);
	void setMat3(const char *name, mat3 mat);
	void setMat4(const char *name, mat4 mat);
private:
	unsigned int m_ID;
	string m_Name;
};

