#pragma once

#include"Page.h"

class Home : public Page {
public:
	virtual void OnRender();
	virtual void OnRenderGUI();
	virtual void OnOpen();
	virtual void OnClose();
	virtual void Update();

};