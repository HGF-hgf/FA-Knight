#pragma once

#include"Page.h"

class PauseMenu : public Page {
public:
	virtual void OnRender();
	virtual void OnRenderGUI();
	virtual void OnOpen();
	virtual void OnClose();
	virtual void Update();

};
