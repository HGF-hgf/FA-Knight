
#include"Input.h"
#include"Engine.h"


using namespace std;

Input* Input::s_Instance = nullptr;
//cap nhat trang thai cac phim tren ban phim

Input::Input() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::HandIn() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
		case SDL_QUIT: Engine::Getinstance()->Quit(); break;
		case SDL_KEYDOWN: KeyDown(); break;
		case SDL_KEYUP: KeyUp(); break;
		}
	}
}

bool Input::GetKeyDown(SDL_Scancode key) {
	if (m_KeyStates[key] == 1)
		return true;
	return false;
	
}

void Input::KeyUp() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
//
int Input::GetAxisKey(Axis axis) {
	switch (axis) {
	case HORIZONTAL:
		if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
			return 1;
		if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
			return -1;
		break;
	case VERTICAL:
		if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP))
			return -1;
		break;
	case ATTACK:
		if (GetKeyDown(SDL_SCANCODE_SPACE))
			return 1;
		break;

	default:
		return 0;
		
	}	
}