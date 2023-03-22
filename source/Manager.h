#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Agent.h"
using namespace std;
using namespace glm;
class Manager {
public:
	static Manager& GetInstance();
	Manager(const Manager&) = delete;
	Manager();
	~Manager();

	vec2 SpawnPoint;
	vec2 GoalPoint;

	int PopulationSize;
	int AgentLifeSpan;
	float AgentSpeed;
	float MutationRate;
	
	vector<Agent> AgentList;
	vector<Agent> MatingPool;
	
	int Generation;
	int CurrGenTime;

	void Init();


	void SpawnAgent();
	void Evaluate();
	void Select();
	
	void Draw();
};

