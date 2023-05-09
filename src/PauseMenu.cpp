#include"PauseMenu.h"
#include"Engine.h"
#include"Texture.h"

void PauseMenu::OnRender()
{

}

void PauseMenu::OnRenderGUI()
{
	
    //back ground
    auto m_backgroundTexure = Texture::Getinstance()->GetTexture("pause-bg");
    auto m_io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(m_io.DisplaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Home Page Background", NULL,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::Image((ImTextureID)m_backgroundTexure,
        ImVec2(m_io.DisplaySize.x, m_io.DisplaySize.y));

    ImGui::PopStyleVar(2);
    ImGui::End();

	//Resume
	auto buttonImage1 = Texture::Getinstance()->GetTexture("game-button-1");
	auto io1 = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io1.DisplaySize.x * 0.5f, io1.DisplaySize.y * 0.4f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("Pause Page Menu", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage1, ImVec2(192, 72))) {

		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Mix_PauseMusic();
		
		Engine::Getinstance()->GoToPage("game");
		
		if (Game::Getinstance()->Getplayer()->GetX() < 3900) {
			Mix_PlayMusic(Engine::Getinstance()->m_music[1], -1);
			Mix_VolumeMusic(5);
		}

		if (Game::Getinstance()->Getplayer()->GetX() < 8700 && Game::Getinstance()->Getplayer()->GetX() > 4000 ) {
			Mix_PlayMusic(Engine::Getinstance()->m_music[4], -1);
			Mix_VolumeMusic(5);
		}

		if (Game::Getinstance()->Getplayer()->GetX() > 8800) {
			Mix_PlayMusic(Engine::Getinstance()->m_music[5], -1);
			Mix_VolumeMusic(5);
		}
	}

	ImGui::PopStyleColor(1);
	ImGui::PopStyleVar(2);
	ImGui::End();


	//Home
	auto buttonImage2 = Texture::Getinstance()->GetTexture("game-button-3");
	auto io2 = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io2.DisplaySize.x * 0.452f, io2.DisplaySize.y * 0.52f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("Pause Page Menu 1", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage2, ImVec2(72, 72))) {
		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Mix_PauseMusic();
		Engine::Getinstance()->GoToPage("home");
		Mix_PlayMusic(Engine::Getinstance()->m_music[0], -1);
		Mix_VolumeMusic(5);

	}

	ImGui::PopStyleColor(1);
	ImGui::PopStyleVar(2);
	ImGui::End();


	//Replay
	auto buttonImage3 = Texture::Getinstance()->GetTexture("game-button-2");
	auto io3 = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io3.DisplaySize.x * 0.548f, io3.DisplaySize.y * 0.52f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("Pause Page Menu 2", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage3, ImVec2(72, 72))) {

		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Mix_PauseMusic();
		Engine::Getinstance()->QuitGame();
		Engine::Getinstance()->GoToPage("game");
		Mix_PlayMusic(Engine::Getinstance()->m_music[1], -1);
		Mix_VolumeMusic(5);
	}

	ImGui::PopStyleColor(1);
	ImGui::PopStyleVar(2);
	ImGui::End();

}

void PauseMenu::OnOpen()
{
    Mix_PlayMusic(Engine::Getinstance()->m_music[2], -1);
    Mix_VolumeMusic(20);
}

void PauseMenu::OnClose()
{

}

void PauseMenu::Update()
{
}