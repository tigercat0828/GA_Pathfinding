#include "Obstacle.h"
#include "Painter.h"

Obstacle::Obstacle() {
}

Obstacle::Obstacle(vec2 position, float width, float height) {
	this->position = position;
	this->width = width;
	this->height = height;
}

void Obstacle::Draw() {
	Painter& paint = Painter::GetInstance();

	paint.SetColor(ColorBlack);
	paint.DrawRectangle2D(position , width , height);

	int e = 3;
	paint.SetColor(ColorViolet);
	paint.DrawRectangle2D(position+ vec2(e,e), width-e-e, height-e-e);
}

void Obstacle::CheckCollide(Agent& agent) {
	
	if (agent.position.x > position.x && agent.position.x < position.x + width) {
		if (agent.position.y > position.y && agent.position.y < position.y + height) {
			agent.isFail = true;
		}
	}
}
