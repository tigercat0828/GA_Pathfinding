#include "Sprite.h"

Sprite::Sprite() {
}

Sprite::Sprite(float x, float y, float width, float height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_VBO = 0;	
	init();
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);	// bind buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);		// unbind buffer
}

Sprite::~Sprite() {
	if (m_VBO != 0) glGenBuffers(1, &m_VBO);
}

void Sprite::init() {
	if (m_VBO == 0) glGenBuffers(1, &m_VBO);
	float vertex[12];
	vertex[0] = m_x;			vertex[1] = m_y;				//  (x,y+h)==========(x+w,y+h)
	vertex[2] = m_x + m_width;	vertex[3] = m_y + m_height;		//    ||      	   ///  ||
	vertex[4] = m_x;			vertex[5] = m_y + m_height;		//    ||        ///     ||
	vertex[6] = m_x;			vertex[7] = m_y;				//	  ||     ///        ||
	vertex[8] = m_x + m_width;	vertex[9] = m_y;				//	  ||  ///           ||
	vertex[10] = m_x + m_width;	vertex[11] = m_y + m_height;	//   (x,y)============(x+w,y)
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);	// bind buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);		// unbind buffer
}
