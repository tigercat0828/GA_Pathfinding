
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>

#include "Agent.h"
#include "Manager.h"
#include "Painter.h"
#include "Utility.h"
Painter& Paint = Painter::GetInstance();
Manager& manager = Manager::GetInstance();
void Agent::GenerateDNA() {
	if (DNA.size() == 0) {
		for (int i = 0; i < manager.AgentLifeSpan; i++) {
			DNA.push_back(glm::circularRand(1.0f));
		}
	}
}

float Agent::CalcFitness() {

	float dist = glm::distance(position, manager.SpawnPoint);
	// if goal get more 10 times score
	// if fail get less 10 times score
	fitness = Utility::Map(dist, 0, 1000, 1000, 0);
	if (isGoal) {
		fitness *= 10;
	}
	else if (isFail) {
		fitness /= 10;
	}
	return fitness;
}



void Agent::PerformBehavior() {
	// out of the world
	if (position.x <= 50 || position.x >= 1000) {
		isFail = true;
	}
	else if (position.y <= 50 || position.y >= 1000) {
		isFail = true;
	}
	if (!isFail && !isGoal) {
		int index = manager.CurrGenTime;
		if (index >= DNA.size()) {
			index--;
		}
		velocity = DNA[index];
		position += velocity * manager.AgentSpeed;
	}
}

vector<vec2> Agent::CrossOver(Agent const& waifu) {
	int DNAsize = DNA.size();
	int mid = Utility::RandomRangeInt(0, DNAsize);
	vector<vec2> childDNA;
	// A : |0123456789|
	// B : |abcdefghij|
	// C : |0123456hij|
	for (int i = 0; i < DNAsize; i++) {
		if (i < mid) {
			childDNA.push_back(this->DNA[i]);
		}
		else {
			childDNA.push_back(waifu.DNA[i]);
		}
	}
	return childDNA;
}

void Agent::Mutation() {
	int mutate = 0;
	for (int i = 0; i < DNA.size(); i++) {
		float rate = Utility::RandomRate();
		if (rate < manager.MutationRate) {
			mutate++;
			cout << mutate << endl;
			cout << "Mutate" << endl;
			DNA[i] = glm::circularRand(1.0f);
		}
	}
}

void Agent::Draw() {
	Painter& painter = Painter::GetInstance();
	painter.SetColor(ColorBlack);
	painter.DrawRectangle2D(position - vec2(8, 8), 16, 16);

	if (isFail) {
		painter.SetColor(ColorGray);
	}
	else if (isGoal) {
		painter.SetColor(ColorGreen);
	}
	else {
		painter.SetColor(ColorCyan);
	}
	
	painter.DrawPoint2D(position);

}

Agent::Agent() {
	position = Manager::GetInstance().SpawnPoint;
	velocity = vec2(0, 0);
	accelerate = vec2(0, 0);
	isFail = false;
	isGoal = false;
	fitness = 1;
	GenerateDNA();
}

Agent::Agent(vector<vec2>const & DNA) {
	position = Manager::GetInstance().SpawnPoint;
	velocity = vec2(0, 0);
	accelerate = vec2(0, 0);
	isFail = false;
	isGoal = false;
	fitness = 1;
	this->DNA = DNA;
}

Agent::~Agent() {

}