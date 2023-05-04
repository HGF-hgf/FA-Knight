#include "Home.h"
#include"Engine.h"
#include "Texture.h"

void Home::OnRender()
{
    
}

void Home::OnRenderGUI()
{
  //back ground
    auto m_backgroundTexure = Texture::Getinstance()->GetTexture("home-bg");
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
  
    //play
	auto buttonImage = Texture::Getinstance()->GetTexture("home-button-0");
    auto io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.15f, io.DisplaySize.y - 400), ImGuiCond_Always, ImVec2(0.5f, 1.0f));
  
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Home Page Menu", NULL,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage, ImVec2(192, 96))) {
        
        Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
        Mix_PauseMusic();
		Engine::Getinstance()->GoToPage("game");
        Mix_PlayMusic(Engine::Getinstance()->m_music[1], -1);
        Mix_VolumeMusic(5);
	}

    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);
    ImGui::End();


    //Quit
    auto buttonImage1 = Texture::Getinstance()->GetTexture("home-button-1");
    auto io1 = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(io1.DisplaySize.x * 0.15f, io1.DisplaySize.y - 400), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Home Page Menu", NULL,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

    if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImage1, ImVec2(192, 96))) {

        Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[4], 0);
        Mix_PauseMusic();
        Engine::Getinstance()->Quit();
    }

    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);
    ImGui::End();
  

}

void Home::OnOpen()
{
    Mix_PlayMusic(Engine::Getinstance()->m_music[0], -1);
    Mix_VolumeMusic(30);
}

void Home::OnClose()
{
  
}

void Home::Update()
{
}
