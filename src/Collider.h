#pragma once

#include"Camera.h"
#include"CollisionHandler.h"



using namespace std;

class Collider {
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x,y,w,h }; } // xet kich thuoc va vi tri hop cua character

	void Set(int x, int y, int w, int h) {
		m_Box = { x - m_Buffer.x, y - m_Buffer.y, w - m_Buffer.w ,h - m_Buffer.h }; // hop check collision cua character
	}

	bool CollideWithMap() {
		return CollisionHandler::GetInstance()->MapCollision(m_Box);
	}

	void Draw();

private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};