#include"GamePage.h"
#include"Engine.h"
#include"Game.h"

void GamePage::OnRender()
{
	Game::Getinstance()->Render();
}

void GamePage::OnRenderGUI()
{
	Game::Getinstance()->RenderGUI();
}

void GamePage::OnOpen()
{
	if (Game::Getinstance() == nullptr || Game::Getinstance()->m_Paused == false)
		Engine::Getinstance()->StartLv(1);
	else {
		Game::Getinstance()->m_Paused = false;
	}
}

void GamePage::OnClose()
{
	if(!Game::Getinstance()->Paused())
		Engine::Getinstance()->QuitGame();
}

void GamePage::Update()
{
	Game::Getinstance()->Update();
}

void GamePage::ContinueGame()
{

}
