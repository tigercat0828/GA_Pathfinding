#pragma once 
#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include <string>
#include <spdlog/spdlog.h>
#include "./imgui/imgui_impl_sdl.h"
#include "./imgui/imgui_impl_opengl3.h"
using std::string;

class Window {
public:
	enum State { PLAY, EXIT};
private:	// Init System Functions
	void InitSDL();
	void InitGL();
	void CreateSDLWindow();
	void CreateGLContext();
	void InitIMGUI();
	void PrintVersionInfo();
public:		// Window Properties Members
	Window(string title, int width, int height);
	string m_title;
	int m_width;
	int m_height;
	SDL_Window *m_window;
	SDL_GLContext m_glContext;
	State m_state;
public:		// Configure Properties Functions
	void SetViewport(int width, int height);
	void SetViewport();
	void ProcessInput();
	void ClearBuffer();
	void SwapBuffer();
	//void RenderIMGUI();
	//void RenderScene();

	void Quit();
public:		// Game Main Loop
	
	
};
