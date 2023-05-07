#include "SpriteAnimation.h"
#include "Texture.h"

SpriteAnimation::SpriteAnimation(bool repeat): Animation(repeat){
	m_LastTime = SDL_GetTicks();
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight,float xScale, float yScale, SDL_RendererFlip flip) {
	// ve dua tren cac bien da duoc khai bao
	Texture::Getinstance()->DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_CurrentFrame, flip);
}


void SpriteAnimation::Update(float dt) {
	// frame hien tai can ve duoc tinh bang cach lay thoi gian hien tai tu SDL_GetTicks() chia cho toc do animation va framecount theo cong thuc
	int m_CurrentTime = SDL_GetTicks();
	if ( m_CurrentTime - m_LastTime > m_AnimationSpeed) {
		m_CurrentFrame = (m_CurrentFrame + 1) % m_FrameCount;
		m_LastTime = m_CurrentTime;
	}
	
}

void SpriteAnimation::SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed) {
	//thiet lap cac gia tri thuoc tinh dung cho hai ham tren

	m_textureID = textureID;
	m_spriteRow = spriteRow;
	m_FrameCount = FrameCount;
	m_AnimationSpeed = animationSpeed;
	if (m_LastAnimation != textureID) {
		m_LastAnimation = textureID;
		m_CurrentFrame = 0;
	}
}

int SpriteAnimation::GetCurrentFrame()
{
	return m_CurrentFrame;
}


