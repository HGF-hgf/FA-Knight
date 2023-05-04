#pragma once
#include"Character.h"

#define BulletSpeed 5.0f
#define BULLET_TICKS 500

class Bullet : public Character
{
public:
	Bullet(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);
	virtual void Update(float dt);
	virtual void OnCollide(Character* source);
	SDL_RendererFlip GetFlipType(SDL_RendererFlip flip) { return m_Flip = flip; };
private:
	void AnimationState();
	int m_tick;
};

