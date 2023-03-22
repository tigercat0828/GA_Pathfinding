#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Utility.h"
using namespace std;
using namespace glm;

class Agent {
public:
	Agent();
	Agent(vector<vec2> const & DNA);
	~Agent();
	vec2 position;
	vec2 velocity;
	vec2 accelerate;
	vector<vec2> DNA;
	bool isFail;
	bool isGoal;
	float fitness;

	void Draw();
	void GenerateDNA();
	float CalcFitness();
	void PerformBehavior();

	vector<vec2> CrossOver(Agent const &waifu);
	void Mutation();

	
private:

};
