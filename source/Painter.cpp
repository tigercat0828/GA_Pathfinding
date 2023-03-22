#include "Painter.h"
Painter &Painter::GetInstance() {
	static Painter *Instance = new Painter();
	return *Instance;
}
void Painter::Init(float width, float height, Shader shader2D, Shader shader3D) {
	m_shader2D = shader2D;
	m_shader3D = shader3D;
	m_drawMode = GL_FILL;
	m_color = ColorWhite;
	m_alpha = 1.0f;
	m_pointSize = 1;
	m_lineWidth = 1;
	m_windowWidth = width;
	m_windowHeight = height;
	SetLineWidth(1);
	SetPointSize(1);
	SetProjMat2D(width, height);
	SetupVAOs();
}
Painter::Painter() {
	
}

void Painter::SetColor(vec3 color) {
	m_color = color;
}

void Painter::SetColor(float R, float G, float B) {
	m_color.x = R;
	m_color.y = G;
	m_color.z = B;
}

void Painter::SetAlpha(float alpha) {
	m_alpha = alpha;
}

void Painter::SendDataToShader2D() {
	m_shader2D.use();
	m_shader2D.setMat4("vsu_projMat", m_projMat2D);
	m_shader2D.setVec3("fsu_color", m_color);
	m_shader2D.setFloat1("fsu_alpha", m_alpha);
}

void Painter::SetPointSize(int size) {
	m_pointSize = size;
	glPointSize(m_pointSize);
}

void Painter::SetLineWidth(int width) {
	m_lineWidth = width;
	glLineWidth(m_lineWidth);
}

void Painter::SetDrawMode(GLenum drawMode) {
	m_drawMode = drawMode;
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);
}

void Painter::SetProjMat2D(int width, int height) {
	m_windowWidth = width;
	m_windowHeight = height;
	float aspect = width / height;
	if (aspect > 1.0f) {
		m_projMat2D = glm::ortho(0.0f, m_windowWidth, m_windowHeight * aspect, 0.0f, -1.0f, 1.0f);
	}
	else {
		m_projMat2D = glm::ortho(0.0f, m_windowWidth / aspect, m_windowHeight, 0.0f, -1.0f, 1.0f);
	}
}

void Painter::SetProjMat3D(int width, int height) {

}

void Painter::DrawPoint2D(vec2 pA) {
	float vertex[2];
	vertex[0] = pA.x;	vertex[1] = pA.y;
	SendDataToShader2D();
	glBindVertexArray(m_VAO_Point2D);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Point2D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void Painter::DrawLine2D(vec2 pA, vec2 pB) {
	float vertex[4];
	vertex[0] = pA.x;	vertex[1] = pA.y;	// A
	vertex[2] = pB.x;	vertex[3] = pB.y;	// B
	SendDataToShader2D();
	glBindVertexArray(m_VAO_Line2D);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Line2D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Painter::DrawRectangle2D(vec2 pA, float width, float height) {
	SendDataToShader2D();								//	B-C
	glBindVertexArray(m_VAO_Rectangle2D);				//	|\|
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Rectangle2D);	//	A-D
	float vertex[12];								
	if (m_drawMode == GL_FILL) {
		vertex[0] = pA.x;				vertex[1] = pA.y;				// A		
		vertex[2] = pA.x + width;		vertex[3] = pA.y + height;	// C		
		vertex[4] = pA.x + width;		vertex[5] = pA.y;				// D		
		vertex[6] = pA.x;				vertex[7] = pA.y;				// A	
		vertex[8] = pA.x;				vertex[9] = pA.y + height;	// B	
		vertex[10] = pA.x + width;	vertex[11] = pA.y + height;	// C	
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	else {
		vertex[0] = pA.x;				vertex[1] = pA.y;				// A		
		vertex[2] = pA.x;				vertex[3] = pA.y + height;	// B		
		vertex[4] = pA.x + width;		vertex[5] = pA.y + height;	// C		
		vertex[6] = pA.x + width;		vertex[7] = pA.y ;			// D		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
	glBindVertexArray(0);
}

void Painter::DrawTriangle2D(vec2 pA, vec2 pB, vec2 pC) {
	SendDataToShader2D();
	float vertex[6];
	vertex[0] = pA.x;	vertex[1] = pA.y;	// A
	vertex[2] = pB.x;	vertex[3] = pB.y;	// B
	vertex[4] = pC.x;	vertex[5] = pC.y;	// C
	glBindVertexArray(m_VAO_Line2D);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Line2D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Painter::DrawTrapezium2D(vec2 pA, vec2 pB, vec2 pC, vec2 pD) {
	SendDataToShader2D();
	glBindVertexArray(m_VAO_Rectangle2D);				//	A-D
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Rectangle2D);	//	|\|
	float vertex[12];								//	B-C
	if (m_drawMode == GL_FILL) {
		vertex[0] = pA.x;				vertex[1] = pA.y;			// A		
		vertex[2] = pC.x;				vertex[3] = pC.y;			// C		
		vertex[4] = pD.x;				vertex[5] = pD.y;			// D		
		vertex[6] = pA.x;				vertex[7] = pA.y;			// A	
		vertex[8] = pB.x;				vertex[9] = pB.y;			// B	
		vertex[10] = pC.x;				vertex[11] = pC.y;			// C	
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	else {
		vertex[0] = pA.x;				vertex[1] = pA.y;			// A		
		vertex[2] = pB.x;				vertex[3] = pB.y;			// B		
		vertex[4] = pC.x;				vertex[5] = pC.y;			// C		
		vertex[6] = pD.x;				vertex[7] = pD.y;			// D		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
	glBindVertexArray(0);
}

void Painter::DrawCircle2D(vec2 pA, float radius) {

	float vertex[c_Edges *2 + 2];	// +2 for center
	vertex[0] = pA.x;	vertex[1] = pA.y;	// center
	for (int i = 1; i < c_Edges + 1; i++) {			// construct a circle
		vertex[i * 2] = pA.x + radius * sincos[i*2];			// x
		vertex[i * 2 + 1] = pA.y + radius * sincos[i*2+1];		// y
	}
	SendDataToShader2D();
	glBindVertexArray(m_VAO_Circle2D);				
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Circle2D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);
	if (m_drawMode == GL_FILL) {
		unsigned int fillIndex[c_Edges];

	}
	else {
		unsigned int lineIndex[c_Edges];
		for (int i = 0; i < c_Edges; i++) lineIndex[i] = i + 1;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_Circle2D);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndex), lineIndex, GL_DYNAMIC_DRAW);
		glDrawElements(GL_LINE_LOOP, c_Edges, GL_UNSIGNED_INT, 0);
	}

}

void Painter::SetupVAOs() {
	m_VAO_Point2D = m_VBO_Point2D = 0;			m_VAO_Point3D = m_VBO_Point3D = 0;
	m_VAO_Line2D = m_VBO_Line2D = 0;			m_VAO_Line3D = m_VBO_Line3D = 0;
	m_VAO_Triangle2D = m_VBO_Triangle2D = 0;	m_VAO_Triangle3D = m_VBO_Triangle3D = 0;
	m_VAO_Trapezium2D = m_VBO_Trapezium2D = 0;	m_VAO_Trapezium3D = m_VBO_Trapezium3D = 0;
	m_VAO_Circle2D = m_VBO_Circle2D = 0;		m_VAO_Circle3D = m_VBO_Circle3D = 0;
	m_VAO_Rectangle2D = m_VBO_Rectangle2D = 0;	m_VAO_Rectangle3D = m_VBO_Rectangle3D = 0;
	// -----------------------------------------------------------------
	SetupObjectAttribute(2, m_VAO_Point2D, m_VBO_Point2D);
	SetupObjectAttribute(2, m_VAO_Line2D, m_VBO_Line2D);
	SetupObjectAttribute(2, m_VAO_Triangle2D, m_VBO_Triangle2D);
	SetupObjectAttribute(2, m_VAO_Rectangle2D, m_VBO_Rectangle2D);
	SetupObjectAttribute(2, m_VAO_Trapezium2D, m_VBO_Trapezium2D);
	SetupObjectAttribute(2, m_VAO_Circle2D, m_VBO_Circle2D, m_EBO_Circle2D);
	// -----------------------------------------------------------------
	SetupObjectAttribute(3, m_VAO_Point3D, m_VBO_Point3D);
	SetupObjectAttribute(3, m_VAO_Line3D, m_VBO_Line3D);
	SetupObjectAttribute(3, m_VAO_Triangle3D, m_VBO_Triangle3D);
	SetupObjectAttribute(3, m_VAO_Rectangle3D, m_VBO_Rectangle3D);
	SetupObjectAttribute(3, m_VAO_Trapezium3D, m_VBO_Trapezium3D);
	SetupObjectAttribute(3, m_VAO_Circle3D, m_VBO_Circle3D);
}

void Painter::SetupObjectAttribute(int D2orD3, unsigned int &VAO, unsigned int &VBO) {
	float *temp = nullptr;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(temp), temp, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, D2orD3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void Painter::SetupObjectAttribute(int D2orD3, unsigned int &VAO, unsigned int &VBO, unsigned int &EBO) {
	float *temp = nullptr;
	float *tmp = nullptr;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(temp), temp, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tmp), tmp, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, D2orD3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	sincos[0] = 0.0f;	sincos[1] = 0.0f;	// center
	for (int i = 1; i < c_Edges + 1; i++) {			// construct a circle
		sincos[i * 2] = std::cos((i - 1) * c_Angle);			// x
		sincos[i * 2 + 1] = std::sin((i - 1) * c_Angle);		// y
	}
}

