#pragma once
#include"Page.h"

class GamePage : public Page {
public:
	virtual void OnRender();
	virtual void OnRenderGUI();
	virtual void OnOpen() ;
	virtual void OnClose() ;
	virtual void Update();
	void ContinueGame();
};