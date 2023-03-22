#include "Shader.h"

void Shader::CheckCompilerError(unsigned int shaderID) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		spdlog::error("Failed to compile shader {}:{}", shaderID);
		spdlog::warn("{}", infoLog);
	}
	else {
		spdlog::info("Shader {:2d} compile success", shaderID);
		// printSource();
	}
}

void Shader::CheckLinkError(const char* programName ,unsigned int programID) {
	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		spdlog::error("Failed to link program {}", programID);
		spdlog::warn("{}", infoLog);
	}
	else {
		spdlog::info("Program {}:{} link success", programID, programName);
	}
}

void Shader::CompileShader(unsigned int &shaderID, string fileName, unsigned int SHADER_TYPE) {
	ifstream shaderFile;
	stringstream shaderStream;
	string shaderString;
	shaderFile.exceptions(ifstream::failbit | istream::badbit);
	try {
		// open > rdbuf to stream > close > to string > to charstr
		shaderFile.open(fileName);
		if (!shaderFile.is_open()) {
			throw std::exception();
		}
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderString = shaderStream.str();
		const char *source = shaderString.c_str();
		// create shader
		shaderID = glCreateShader(SHADER_TYPE);
		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);
		CheckCompilerError(shaderID);
	}
	catch (const std::exception &ex) {
		spdlog::error("Failed to load shader file \"{}\": {}", fileName, ex.what());
	}
}

void Shader::LinkProgram(const char *programName, unsigned int &programID, unsigned int vertexShaderID, unsigned int fragmentShaderID) {
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	CheckLinkError(programName, programID);
}

Shader::Shader() {
	m_ID = 0;
}

Shader::Shader(string name, string shaderPath){
	m_Name = name;
	unsigned int vertexShaderID, fragmentShaderID;
	string vsFilePath = shaderPath + ".vs.glsl";
	string fsFilePath = shaderPath + ".fs.glsl";
	CompileShader(vertexShaderID, vsFilePath, GL_VERTEX_SHADER);
	CompileShader(fragmentShaderID, fsFilePath, GL_FRAGMENT_SHADER);
	LinkProgram(m_Name.c_str(), m_ID, vertexShaderID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::use() {
	glUseProgram(m_ID);
}

void Shader::checkUniformLocation(const char *name, unsigned int location) {
	if (location == GL_INVALID_INDEX) {
		spdlog::warn("uniform \"{}\" is not found in shader {}:{}", name, m_ID, m_Name);
	}
}

void Shader::setInt1(const char *name, int v1) {
	//glUniform1i(glGetUniformLocation(m_ID, name), v1);
	unsigned int location = glGetUniformLocation(m_ID, name);
	checkUniformLocation(name, location);
	glUniform1i(location, v1);
}

void Shader::setInt2(const char *name, int v1, int v2) {
	//glUniform2i(glGetUniformLocation(m_ID, name), v1, v2);
	unsigned int location = glGetUniformLocation(m_ID, name);
	checkUniformLocation(name, location);
	glUniform2i(location, v1, v2);
}

void Shader::setInt3(const char *name, int v1, int v2, int v3) {
	//glUniform3i(glGetUniformLocation(m_ID, name), v1, v2, v3);
	unsigned int location = glGetUniformLocation(m_ID, name);
	checkUniformLocation(name, location);
	glUniform3i(location, v1, v2, v3);
}

void Shader::setInt4(const char *name, int v1, int v2, int v3, int v4) {
	//glUniform4i(glGetUniformLocation(m_ID, name), v1, v2, v3, v4);
	unsigned int location = glGetUniformLocation(m_ID, name);
	checkUniformLocation(name, location);
	glUniform4i(location, v1, v2, v3, v4);
}
void Shader::setFloat1(const char *name, float v1) {
	//glUniform1f(glGetUniformLocation(m_ID, name), v1);
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform1f(location, v1);
	checkUniformLocation(name, location);
}

void Shader::setFloat2(const char *name, float v1, float v2) {
	//glUniform2f(glGetUniformLocation(m_ID, name), v1, v2);
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform2f(location, v1, v2);
	checkUniformLocation(name, location);
}

void Shader::setFloat3(const char *name, float v1, float v2, float v3) {
	//glUniform3f(glGetUniformLocation(m_ID, name), v1, v2, v3);
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform3f(location, v1, v2, v3);
	checkUniformLocation(name, location);
}

void Shader::setFloat4(const char *name, float v1, float v2, float v3, float v4) {
	//glUniform4f(glGetUniformLocation(m_ID, name), v1, v2, v3, v4);
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform4f(location, v1, v2, v3, v4);
	checkUniformLocation(name, location);
}

void Shader::setVec2(const char *name, vec2 vec) {
	//glUniform2fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(vec));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform2fv(location, 1, glm::value_ptr(vec));
	checkUniformLocation(name, location);
}

void Shader::setVec3(const char *name, vec3 vec) {
	//glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(vec));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform3fv(location, 1, glm::value_ptr(vec));
	checkUniformLocation(name, location);
}

void Shader::setVec4(const char *name, vec3 vec) {
	//glUniform4fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(vec));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniform4fv(location, 1, glm::value_ptr(vec));
	checkUniformLocation(name, location);
}

void Shader::setMat2(const char *name, mat2 mat) {
	//glUniformMatrix2fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	checkUniformLocation(name, location);
}

void Shader::setMat3(const char *name, mat3 mat) {
	//glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	checkUniformLocation(name, location);
}

void Shader::setMat4(const char *name,mat4 mat) {
	//glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(mat));
	unsigned int location = glGetUniformLocation(m_ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	checkUniformLocation(name, location);
}