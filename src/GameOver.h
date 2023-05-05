#pragma once
#include"Page.h"

class GanmeOver : public Page {
public:
	virtual void OnRender();
	virtual void OnRenderGUI();
	virtual void OnOpen();
	virtual void OnClose();
	virtual void Update();

};
