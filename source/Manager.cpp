#include "Manager.h"
#include "Painter.h"
#include <glm/glm.hpp>
using namespace glm;

Manager& Manager::GetInstance() {
	static Manager* Instance = new Manager();
	return *Instance;
}

Manager::Manager() {

}

Manager::~Manager() {
}

void Manager::Init() {
	SpawnPoint = vec2(500, 100);
	GoalPoint = vec2(500, 900);
	PopulationSize = 80;
	AgentLifeSpan = 500;
	MutationRate = 0.05f;
	Generation = 0;
	CurrGenTime = 0;
	AgentSpeed = 8.0f;
}

void Manager::SpawnAgent() {
	for (int i = 0; i < PopulationSize; i++) {
		AgentList.push_back(Agent());
	}
}

void Manager::Evaluate() {
	// figure out the max fitness
	float maxFitness= -1;
	for (auto& agent : AgentList) {
		float fit = agent.CalcFitness();
		if (fit > maxFitness) {
			maxFitness = fit;
		}
	}
	/*
	for (int i = 0; i < AgentList.size(); i++) {
		printf("Agent %d fitness = %f\n", i, AgentList[i].fitness);
	}
	*/
	// normalize the fitness
	for (auto& agent : AgentList) {
		agent.fitness /= maxFitness;
	}
	for (int i = 0; i < PopulationSize; i++) {
		int n = AgentList[i].fitness * 100;
		for (int  j = 0; j < n; j++) {
			MatingPool.push_back(AgentList[i]);
		}
	}
}

void Manager::Select() {
	AgentList.clear();
	cout << "MatingPool size = " << Manager::GetInstance().MatingPool.size() << endl;
	for (int i = 0; i < PopulationSize; i++) {
		int indexA = Utility::RandomRangeInt(0, MatingPool.size());
		int indexB = Utility::RandomRangeInt(0, MatingPool.size());
		Agent parentA = MatingPool[indexA];
		Agent parentB = MatingPool[indexB];
		vector<vec2> newDNA = parentA.CrossOver(parentB);
		Agent child(newDNA);
		AgentList.push_back(child);
	}
	MatingPool.clear();
	for (auto& agent : AgentList) {
		agent.Mutation();
	}
}


void Manager::Draw() {
	Painter& Paint = Painter::GetInstance();
	Manager& manager = Manager::GetInstance();
	Paint.SetColor(ColorRed);
	Paint.DrawPoint2D(manager.SpawnPoint);
	Paint.SetColor(ColorGreen);
	Paint.DrawPoint2D(manager.GoalPoint);
}
