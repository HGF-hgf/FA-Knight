#include"Engine.h"
#include"GameObject.h"
#include"Texture.h"
#include"Input.h"
#include"Player.h"
#include"Timer.h"
#include"MapParser.h"
#include"Camera.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Soul.h"
#include"Home.h"
#include"GamePage.h"
#include"PauseMenu.h"
#include"GameOver.h"
#include"End.h"

using namespace std;

Engine* Engine::s_Instance = nullptr;
//Player* player = nullptr;
bool Engine::Init() {

	int init = Mix_Init(0);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	

	Mix_Music* home = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/home.wav");
	m_music.push_back(home);//0
	Mix_Music* lv1 = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/lv1.wav");
	m_music.push_back(lv1);//1
	Mix_Music* pause = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/Pause.wav");
	m_music.push_back(pause);//2
	Mix_Music* gameover = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/die.wav");
	m_music.push_back(gameover);//3
	Mix_Music* lv2 = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/lv2.wav");
	m_music.push_back(lv2);//4
	Mix_Music* lv3 = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/lv3.wav");
	m_music.push_back(lv3);//5
	Mix_Music* ending = Mix_LoadMUS("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/ending.wav");
	m_music.push_back(ending);//6

	/*if (!home) {
		cout << "Failed\n" << Mix_GetError();
	}*/



	Mix_Chunk* jump = Mix_LoadWAV("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/sfx_movement_jump1.wav");
	m_sfx.push_back(jump);//0
	Mix_VolumeChunk(jump, 20);

	Mix_Chunk* land = Mix_LoadWAV("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/sfx_sounds_impact1 (landing).wav");
	m_sfx.push_back(land);//1
	Mix_VolumeChunk(land, 20);

	Mix_Chunk* attack = Mix_LoadWAV("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/shuriken2.wav");
	m_sfx.push_back(attack);//2
	Mix_VolumeChunk(attack, 10);

	Mix_Chunk* hit = Mix_LoadWAV("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/impact2.wav");
	m_sfx.push_back(hit);//3
	Mix_VolumeChunk(hit, 10);

	Mix_Chunk* click = Mix_LoadWAV("C:/Users/PC/Desktop/hgf/Project1/texture/sfx/click2.wav");
	m_sfx.push_back(click);//4
	Mix_VolumeChunk(click, 40);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("FAILED TO INITIALIZE SDL\n", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0 || IMG_Init(IMG_INIT_JPG) == 0)
		std::cout << "shit";

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("FAILED TO INITIALIZE SDL\n", SDL_GetError());
		return false;
	}

	
	
	SDL_WindowFlags  window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("FA Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("FAILED TO CREATE WINDOW\n", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("FAILED TO CREATE RENDERER\n", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		cout<<"Failed to load map\n";
		return false;
	}
	cout << m_lv << endl;
	

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
	ImGui_ImplSDLRenderer_Init(m_Renderer);
	PageMap["home"] = new Home;
	PageMap["game"] = new GamePage;
	PageMap["pause"] = new PauseMenu;
	PageMap["gameover"] = new GanmeOver;
	PageMap["end"] = new End;

	GoToPage("home");
	
	Texture::Getinstance()->ParseTexture(RESOURCE_PATH + "textures.tml");

 	return m_isRunning = true;


}


void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 164, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	PageMap[currentPage]->OnRender();

	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	PageMap[currentPage]->OnRenderGUI();
	

	ImGui::Render();


	// Rendering
	ImGui_ImplSDLRenderer_RenderDrawData(
		ImGui::GetDrawData()
	);

	SDL_RenderPresent(m_Renderer);
	
}

void Engine::Update() {
	PageMap[currentPage]->Update();
	if (ChangeLv) {
		StartLv(game->lv + 1);
		m_lv++;
		ChangeLv = false;
	}
	//LevelSet();
	
}



void Engine::Events() {
	Input::GetInstance()->HandIn();
}

void Engine::GoToPage(string name)
{
	if (currentPage != "") {
		PageMap[currentPage]->OnClose();
	}
	currentPage = name;
	PageMap[currentPage]->OnOpen();
}

//void Engine::StartGame()
//{
//	game = new Game(0, 2, 0);
//}

void Engine::QuitGame()
{
	if (game != nullptr)
	{
		delete game;
		game = nullptr;
		Game::s_Instance = nullptr;
	}
}

void Engine::Resume()
{
	
}

void Engine::StartLv(int lv)
{
	int score = 0, time = 0;
	if (game) {
		score = game->m_Score;
		time = game->m_Time;
		QuitGame();
	}
	game = new Game(score, lv, time);
}

//bool Engine::LevelSet()
//{
//	if (!MapParser::GetInstance()->Load()) {
//		cout << "Failed to load map\n";
//		return false;
//	}
//	cout << m_lv << endl;
//}



void Engine::Clean() {

	for (unsigned int i = 0;i != m_GameObjects.size();i++) {
		m_GameObjects[i]->Clean();
	}
	Texture::Getinstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();

}

void Engine::Quit() {
	m_isRunning = false;
}

//float Engine::SetBotPos() {
//
//}

