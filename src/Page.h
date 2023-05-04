#pragma once

class Page {
public:
	virtual void OnRender() {};
	virtual void OnRenderGUI() = 0;
	virtual void OnOpen() = 0;
	virtual void OnClose() = 0;
	virtual void Update() {};
};