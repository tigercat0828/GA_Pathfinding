#pragma once 
#include <glad/glad.h>
class Sprite {
public:
	Sprite();
	Sprite(float x, float y, float width, float height);
	void draw();
	~Sprite();
private:
	unsigned int m_VBO;
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	void init();
};
