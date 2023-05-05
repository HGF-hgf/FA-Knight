#include"Game.h"
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

	int time = m_Time;
	int min = time / 60;
	int sec = time % 60;
	minstr = (min < 10 ? "0" : "") + to_string(min);
	secstr = (sec < 10 ? "0" : "") + to_string(sec);

	Engine::Getinstance()->m_min = minstr;
	Engine::Getinstance()->m_sec = secstr;
	Engine::Getinstance()->p_score = m_Score;

	//Pause
	if (!player->dead) {
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.0f;
		auto buttonImage = Texture::Getinstance()->GetTexture("game-button-0");
		auto io = ImGui::GetIO();

		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.23f, io.DisplaySize.y * 0.07f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

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
		ImGui::SameLine();
		ImGui::SetWindowFontScale(3);
		ImGui::Text("Score: %d     ", m_Score);
		ImGui::SameLine();
		ImGui::Text("Time: %s:%s ", minstr.c_str(), secstr.c_str());

		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
		ImGui::End();
	}

	if (player->dead) {
		Engine::Getinstance()->GoToPage("gameover");
		//Mix_PauseMusic;
		//auto m_backgroundTexure = Texture::Getinstance()->GetTexture("die-bg");
		//auto m_io = ImGui::GetIO();
		//ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		//ImGui::SetNextWindowSize(m_io.DisplaySize);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		//ImGui::Begin("Home Page Background", NULL,
		//	ImGuiWindowFlags_NoDecoration |
		//	ImGuiWindowFlags_NoScrollbar |
		//	ImGuiWindowFlags_NoBringToFrontOnFocus |
		//	ImGuiWindowFlags_NoResize |
		//	ImGuiWindowFlags_NoScrollWithMouse);

		//ImGui::Image((ImTextureID)m_backgroundTexure,
		//	ImVec2(m_io.DisplaySize.x, m_io.DisplaySize.y));

		//ImGui::PopStyleVar(2);
		//ImGui::End();

		//auto buttonImage2 = Texture::Getinstance()->GetTexture("game-button-3");
		//auto buttonImage3 = Texture::Getinstance()->GetTexture("game-button-2");
		//auto io2 = ImGui::GetIO();

		//ImGui::SetNextWindowPos(ImVec2(io2.DisplaySize.x * 0.5f, io2.DisplaySize.y * 0.55f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		//ImGui::Begin("Pause Page Menu 1", NULL,
		//	ImGuiWindowFlags_NoTitleBar |
		//	ImGuiWindowFlags_NoScrollbar |
		//	ImGuiWindowFlags_NoResize |
		//	ImGuiWindowFlags_AlwaysAutoResize);
		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

		//ImGui::SetWindowFontScale(3);
		//ImGui::Text("Score: %d", m_Score);
		//ImGui::Text("Time: %s:%s ", minstr.c_str(), secstr.c_str());
	
		//if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage2, ImVec2(96, 96))) {
		//	Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		//	Engine::Getinstance()->GoToPage("home");
		//}
		//ImGui::SameLine();
		//if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage3, ImVec2(96, 96))) {

		//	Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		//	Mix_PauseMusic();
		//	//Engine::Getinstance()->QuitGame();
		//	Engine::Getinstance()->GoToPage("game");
		//	Mix_PlayMusic(Engine::Getinstance()->m_music[1], -1);
		//	Mix_VolumeMusic(5);
		//}

		//
		//ImGui::PopStyleColor();
		//ImGui::PopStyleVar(2);
		//ImGui::End();
	}

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
	if (!player->dead) {
		m_Time += dtTime / 1000;
		m_lasttIme = currentTime;
	}
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