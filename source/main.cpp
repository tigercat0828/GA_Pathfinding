#include <iostream>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>
#include "Xavier.h"
#include "Agent.h"
#include "Manager.h"
#include "Obstacle.h"
using namespace std;
using namespace glm;

int main(int argc, char** argv) {

	Window Game("GA", 1000, 1000);	// create window
	Shader Canvas2DRenderer("Canvas2DRenderer", "./shader/Canvas2DRenderer");
	Painter& Paint = Painter::GetInstance();
	Paint.Init(Game.m_width, Game.m_height, Canvas2DRenderer, Canvas2DRenderer);
	Paint.SetPointSize(10);
	Game.SetViewport();
	// INIT
	// ---------------------------------------------------
	Manager& manager = Manager::GetInstance();
	manager.Init();
	manager.SpawnAgent();
	int& MaxGenTime = manager.AgentLifeSpan;
	vector<Obstacle> walls;
	walls.push_back(Obstacle(vec2(250, 250), 100, 600));
	//walls.push_back(Obstacle(vec2(350, 450), 300, 100));
	walls.push_back(Obstacle(vec2(650, 250), 100, 600));
	Obstacle o(vec2(100, 100), 100, 100);
	// ----------------------------------------------------
	while (Game.m_state != Window::State::EXIT) {
		Game.ClearBuffer();
		Game.ProcessInput();
		// LOGIC
		//------------------------------------------------

		for (auto &agent : manager.AgentList) {
			agent.PerformBehavior();
		}

		// check if collide with the walls
		for (auto &wall : walls) {
			for (auto& agent : manager.AgentList) {
				wall.CheckCollide(agent);
			}
		}
		
		if (manager.CurrGenTime >= manager.AgentLifeSpan) {
			// Next Generation
			manager.Generation++;
			manager.CurrGenTime = 0;
			manager.Evaluate();
			manager.Select();
		}
		else {
			manager.CurrGenTime++;
		}
		// RENDER
		//------------------------------------------------

		manager.Draw();
		for (auto& w : walls) {
			w.Draw();
		}
		for (auto& agent : manager.AgentList) {
			agent.Draw();
		}
		//------------------------------------------------
		Game.SwapBuffer();
	}
	Game.Quit();
	return EXIT_SUCCESS;
}
