#pragma once
#include <glm/glm.hpp>
#include "Agent.h"
using namespace glm;
class Obstacle {
public:
		
	Obstacle();
	Obstacle(vec2 position, float width, float height);
	
	vec2 position;
	float width;
	float height;

	void Draw();
	void CheckCollide(Agent& agent);
private:

};

