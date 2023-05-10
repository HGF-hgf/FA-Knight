#pragma once

#include"GameObject.h"
#include"Map.h"
#include"Player.h"
#include"Bullet.h"
#include"Portal.h"

class Game {
public:
	Game(int score, int lv, float time);

	static Game* Getinstance() {
		return s_Instance;
	}
	void RenderGUI();
	void GameMenu();
	void Render();
	void Update();
	void addCharacter(GameObject* object);
	void removeCharacter(GameObject* object);


	Player* Getplayer() { return player; }
	vector<int> m_x = { 1044, 1518, 4470, 4593, 4690, 4822, 10154, 10358 };
	vector<int> m_y = { 489,489,456,456,456,456,617,617 };
	std::unordered_map<int, GameObject*> m_GameObjects;
	inline Map* GetMap() { return m_LevelMap; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };
	inline bool Paused() { return m_Paused; }
	//inline bool Ended() { return m_Ended; }
	static Game* s_Instance;

	bool m_Paused = false;
	bool m_Ended = false;
	int m_Score = 0;
	float m_Time = 0;
	int lv;
	string minstr;
	string secstr;
private:
	
	float SetBotPos();
	Map* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Player* player;
	Enemy* enemy;
	float m_lasttIme;
	

};