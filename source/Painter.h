#pragma once 
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Constant.h"
using glm::vec2;
using glm::vec3;
using glm::mat4;
// use singleton design-mode

class Painter {

public:
	static Painter &GetInstance();
	void Init(float width, float height,Shader shader2D, Shader shader3D);
private:
	constexpr static int c_Edges = 48;
	constexpr static float c_Angle = glm::radians(360.0f / c_Edges);

private:	// pro
	Painter(const Painter &) = delete;
	Painter();
	mat4 m_projMat2D;
	mat4 m_projMat3D;
	mat4 m_viewMat3D;
	mat4 m_viewMat2D;
	int m_pointSize;
	int m_lineWidth;
	float m_alpha;
	vec3 m_color;
	Shader m_shader2D;
	Shader m_shader3D;
	GLenum m_drawMode;
	float m_windowHeight;
	float m_windowWidth;
public:		// Configure Draw Way
	void SetPointSize(int size);
	void SetLineWidth(int width);
	void SetDrawMode(GLenum drawMode);
	void SetProjMat2D(int width, int height);
	void SetProjMat3D(int width, int height);
	void SetColor(vec3 color);
	void SetColor(float R, float G, float B);
	void SetAlpha(float alpha);
public:		// 2D Canvas Primitive Draw Function
	void DrawPoint2D(vec2 pA);
	void DrawLine2D(vec2 pA, vec2 pB);
	void DrawRectangle2D(vec2 pA, float width, float height);
	void DrawTriangle2D(vec2 pA, vec2 pB, vec2 pC);
	void DrawTrapezium2D(vec2 pA, vec2 pB, vec2 pointC, vec2 pointD);
	void DrawCircle2D(vec2 pA, float radius);
public:		// 3D Canvas Primitive Draw Function
	void DrawPoint3D(vec3 pA);
	void DrawLine3D(vec3 pA, vec3 pB);
	void DrawRectangle3D(vec3 pA, vec3 pB, float width, float height);
	void DrawTriangle3D(vec3 pA, vec3 pB, vec3 pC);
	void DrawTrapezium3D(vec3 pA, vec3 pB, vec3 pC, vec3 pD);
	void DrawCircle3D(vec3 pA, float radius);
private:	// VBO, VAO, member variable and function
	void SetupVAOs();
	void SetupObjectAttribute(int D2orD3, unsigned int &VAO, unsigned int &VBO);
	void SetupObjectAttribute(int D2orD3, unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);
	unsigned int m_VAO_2D;
	unsigned int m_VAO_3D;
	unsigned int m_VAO_Point2D, m_VBO_Point2D;			unsigned int m_VAO_Point3D, m_VBO_Point3D;
	unsigned int m_VAO_Line2D, m_VBO_Line2D;			unsigned int m_VAO_Line3D, m_VBO_Line3D;
	unsigned int m_VAO_Triangle2D, m_VBO_Triangle2D;	unsigned int m_VAO_Triangle3D, m_VBO_Triangle3D;
	unsigned int m_VAO_Rectangle2D, m_VBO_Rectangle2D;	unsigned int m_VAO_Rectangle3D, m_VBO_Rectangle3D;
	unsigned int m_VAO_Trapezium2D, m_VBO_Trapezium2D;	unsigned int m_VAO_Trapezium3D, m_VBO_Trapezium3D;
	unsigned int m_VAO_Circle2D, m_VBO_Circle2D, m_EBO_Circle2D;
	unsigned int m_VAO_Circle3D, m_VBO_Circle3D, m_EBO_Circle3D;
	float sincos[c_Edges*2+2];
	void SendDataToShader2D();
	void SendDataToShader3D();
};

