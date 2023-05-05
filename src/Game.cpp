#include "Game.h"
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
#include"Engine.h"

Game* Game::s_Instance = nullptr;

Game::Game(int score, int lv, float time)
{
	s_Instance = this;

	m_Time = time;
	m_Score = score;
	this->lv = lv;
	m_lasttIme = SDL_GetTicks();

	m_LevelMap = MapParser::GetInstance()->GetMap("Level" + to_string(lv));
	
	

	
	player = new Player(new Properties("player", 60, 200, 128, 128), 1, 6, 150, -48, -44, -30, -52);
	addCharacter(player);

	for (int i = 0; i < 3;++i) {
		Enemy* enemy = new Enemy(new Properties("enemy", /*rand() % (1280 - 640 + 1) +*/ 600 * i  /*i*350*/, 93 + 35 /*+ rand() % (573 - 320 + 1) + 320*/, 192, 192), 1, 4, 150, -68, -34, -50, -93);
		addCharacter(enemy);
	}

	/*for (int i = 0; i < 1;++i) {
		Soul* soul = new Soul(new Properties("soul", 600, 128, 128, 128), 1, 5, 150, -48, -30, -30, -76);
		addCharacter(soul);
	}*/

	Camera::GetInstance()->SetTarget(player->GetOrigin());

}

void Game::Render()
{
	Texture::Getinstance()->Draw("bg", 0, 0, 1920, 1080, 1, 0.9, 0.3);

	m_LevelMap->Render();

	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		object->Draw();

		if (((Character*) object)->GetName() == "enemy") {
			Enemy* enemy = (Enemy*)object;
			Vector2D cam = Camera::GetInstance()->GetPosition();
			SDL_Rect m_Box = enemy->GetSwordBox();
			SDL_Rect box = { (int)(m_Box.x - cam.X), (int)(m_Box.y - cam.Y), m_Box.w,  m_Box.h };
			SDL_RenderDrawRect(Engine::Getinstance()->GetRenderer(), &box);
		}
	}
	
}

void Game::RenderGUI() {

	//Pause
	auto buttonImage = Texture::Getinstance()->GetTexture("game-button-0");
	auto io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.02f, io.DisplaySize.y * 0.07f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("Game Page Menu", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage, ImVec2(36, 36))) {

		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Mix_PauseMusic();
		m_Paused = true;
		Engine::Getinstance()->GoToPage("pause");
	}

	ImGui::PopStyleColor(1);
	ImGui::PopStyleVar(2);
	ImGui::End();

	int time = m_Time;
	int min = time / 60;
	int sec = time % 60;
	string minstr = (min < 10 ? "0" : "") + to_string(min);
	string secstr = (sec < 10 ? "0" : "") + to_string(sec);

	auto io1 = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(io1.DisplaySize.x * 0.18f, io1.DisplaySize.y * 0.07f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));
	ImGui::Begin("Score", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2);
	ImGui::Text("Score: %d     ", m_Score);
	ImGui::SameLine();
	ImGui::Text("Time: %s:%s", minstr.c_str(), secstr.c_str());
	ImGui::End();



}



void Game::Update()
{
	for (auto& it1 : m_GameObjects) {
		Character* ch1 = (Character*)it1.second;

		for (auto& it2 : m_GameObjects) {
			Character* ch2 = (Character*)it2.second;

			if (ch1 != ch2 && CollisionHandler::GetInstance()->checkCollision(ch1->GetBox(), ch2->GetBox()))
			{
				ch1->OnCollide(ch2);
			}
		}
	}

	float dt = Timer::Getinstance()->GetDeltaTime();
	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		object->Update(dt);
	}

	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);

	std::vector<int> m_removedIds;

	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		Character* character = (Character*)object;

		if (character->IsDead())
			m_removedIds.push_back(character->GetId());
		

	}

	for (auto& id : m_removedIds)
		removeCharacter(m_GameObjects[id]);

	float currentTime = SDL_GetTicks();
	float dtTime = currentTime - m_lasttIme;
	m_Time += dtTime / 1000;
	m_lasttIme = currentTime;
}


void Game::addCharacter(GameObject* object)
{
	m_GameObjects[object->GetId()] = object;
}

void Game::removeCharacter(GameObject* object)
{
	m_GameObjects.erase(object->GetId());
	delete object;
}