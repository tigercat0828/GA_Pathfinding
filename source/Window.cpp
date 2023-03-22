#include "Window.h"
#include "Manager.h"
using std::cerr;
using std::endl;
using std::cout;

void ErrorTip(string errorString1 , string errorString2) {
	cerr << errorString1 << errorString2 << endl;;
}
Window::Window(std::string title, int width, int height) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_state = State::PLAY;
	InitSDL();
	CreateSDLWindow();
	CreateGLContext();
	InitGL();
	InitIMGUI();
	PrintVersionInfo();
}

void Window::InitSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cerr << "[ERROR] FAILED TO INIT SDL::" << SDL_GetError() << endl;
	}
}

void Window::InitGL() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		cout << "[ERROR] Failed to initial glad" << endl;
	}
	glClearColor(0, 0, 0, 1);
}

void Window::CreateSDLWindow() {
	m_window = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	if (m_window == nullptr) {
		ErrorTip("[ERROR] FAILED TO CREATE WINDOW::", SDL_GetError());
	}
}

void Window::CreateGLContext() {
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr) {
		ErrorTip("[ERROR] FAILED TO CREATE OPENGL CONTEXT", SDL_GetError());
	}
	else {
		SDL_GL_MakeCurrent(m_window, m_glContext);
	}
}

void Window::InitIMGUI() {
	// setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	// setup Dear ImGui style
	ImGui::StyleColorsDark();
	// setup platform/renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Window::PrintVersionInfo() {
	spdlog::info("Welcome to Xavier Engine");
	spdlog::info("   Vendor: {0}", glGetString(GL_VENDOR));
	spdlog::info(" Renderer: {0}", glGetString(GL_RENDERER));
	spdlog::info("  Version: {0}", glGetString(GL_VERSION));
	spdlog::info(" GLSL ver: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	cout << "====================================================================" << endl;
}


void Window::SetViewport(int width, int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}

void Window::SetViewport() {
	glViewport(0, 0, m_width, m_height);
}

void Window::ProcessInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_state = State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//printf("mousePos(x,y) = (%3d,%3d)\n", evnt.motion.x, evnt.motion.y);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			m_width = evnt.window.data1;
			m_height = evnt.window.data2;
			printf("(w, h) = (%d, %d)\n", m_width, m_height);
		};
	}
	ImGui_ImplSDL2_ProcessEvent(&evnt);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	// a window is defined by Begin/End pair
	{
		static int counter = 0;
		// get the window size as a base for calculating widgets geometry
		int sdl_width = 0, sdl_height = 0, controls_width = 0;
		SDL_GetWindowSize(m_window, &sdl_width, &sdl_height);
		controls_width = sdl_width;
		// make controls widget width to be 1/3 of the main window width
		if ((controls_width /= 3) < 300) { controls_width = 300; }
		// position the controls widget in the top-right corner with some margin
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
		// here we set the calculated width and also make the height to be
		// be the height of the main window also with some margin
		ImGui::SetNextWindowSize(
			ImVec2(static_cast<float>(200), static_cast<float>(200)),
			ImGuiCond_Always
		);
		// create a window and append into it
		ImGui::Begin("DashBoard", NULL, ImGuiWindowFlags_NoResize);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform" );
		ImGui::SameLine();
		ImGui::Text("%s", SDL_GetPlatform());
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		
		Manager& manager = Manager::GetInstance();
		// -------------------------------------------------------------------------------
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "SpawnPoint");
		ImGui::SameLine();
		ImGui::Text("(%.0f, %.0f)", manager.SpawnPoint.x, manager.SpawnPoint.y);
		
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), " GoalPoint");
		ImGui::SameLine();
		ImGui::Text("(%.0f, %.0f)", manager.GoalPoint.x, manager.GoalPoint.y);
		// -------------------------------------------------------------------------------
		ImGui::Dummy(ImVec2(0.0f, 2.0f));
		// -------------------------------------------------------------------------------
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Generation");
		ImGui::SameLine();
		ImGui::Text("%d", manager.Generation);

		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Current Time");
		ImGui::SameLine();
		ImGui::Text("%d", manager.CurrGenTime);
		// -------------------------------------------------------------------------------
		ImGui::Dummy(ImVec2(0.0f, 2.0f));
		// -------------------------------------------------------------------------------
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "Population ");
		ImGui::SameLine();
		ImGui::Text("%d", manager.AgentList.size());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "Lifespan ");
		ImGui::SameLine();
		ImGui::Text("%d", manager.AgentLifeSpan);
		ImGui::End();


		// buttons and most other widgets return true when clicked/edited/activated
	}
	// rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::ClearBuffer() {
	glClearColor(0.2, 0.2, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Quit() {
	if (m_window) SDL_DestroyWindow(m_window);
	if (m_glContext) SDL_GL_DeleteContext(m_glContext);
	SDL_Quit();
}

void Window::SwapBuffer() {
	SDL_GL_SwapWindow(m_window);
}
