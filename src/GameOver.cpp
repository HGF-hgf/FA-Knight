#include "GameOver.h"
#include"Texture.h"
#include"Engine.h"

void GanmeOver::OnRender()
{
}

void GanmeOver::OnRenderGUI()
{
	auto m_backgroundTexure = Texture::Getinstance()->GetTexture("die-bg");
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

	auto buttonImage2 = Texture::Getinstance()->GetTexture("game-button-3");
	auto buttonImage3 = Texture::Getinstance()->GetTexture("game-button-2");
	auto io2 = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io2.DisplaySize.x * 0.5f, io2.DisplaySize.y * 0.55f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("Pause Page Menu 1", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	ImGui::SetWindowFontScale(3);
	ImGui::Text("Enemies Killed: %d", Engine::Getinstance()->p_score);
	ImGui::Text("Time: %s:%s ", Engine::Getinstance()->m_min.c_str(), Engine::Getinstance()->m_sec.c_str());

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage2, ImVec2(96, 96))) {
		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Engine::Getinstance()->GoToPage("home");
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage3, ImVec2(96, 96))) {

		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
		Mix_PauseMusic();
		//Engine::Getinstance()->QuitGame();
		Engine::Getinstance()->GoToPage("game");
		Mix_PlayMusic(Engine::Getinstance()->m_music[1], -1);
		Mix_VolumeMusic(5);
	}


	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::End();
}

void GanmeOver::OnOpen()
{
	Mix_PlayMusic(Engine::Getinstance()->m_music[3], -1);
	Mix_VolumeMusic(30);
}

void GanmeOver::OnClose()
{
}

void GanmeOver::Update()
{
}
