#pragma once
#include"Animation.h"


class SpriteAnimation : public Animation
{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight,float Xscale, float yScale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed);
	int GetCurrentFrame();
private:
	int m_AnimationSpeed;//toc do hien thi cua cac animation
	int m_spriteRow;//so hang
	int m_FrameCount;//dem so frame can ve
	string m_textureID;//ten cua doi tuong can ve
};

