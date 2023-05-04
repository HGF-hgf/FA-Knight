#include "SoulBullet.h"
#include "Input.h"
#include "Player.h"
#include "Engine.h"

SoulBullet::SoulBullet(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(0.0f);
	m_IsRunning = true;
	m_tick = SDL_GetTicks();
}

void SoulBullet::Update(float dt) {
	m_Rigidbody->UnsetForce();
	if (m_Flip == SDL_FLIP_NONE) {
		m_Rigidbody->ApplyForceX(FORWARD * BulletSpeed);
	}

	if (m_Flip == SDL_FLIP_HORIZONTAL) {
		m_Rigidbody->ApplyForceX(BACKWARD * BulletSpeed);
	}



	int currentTick = SDL_GetTicks();
	if (currentTick - m_tick > BULLET_TICKS)
	{
		kill();
	}

	if (m_Transform->X == COLUMN * 32 - 32 || m_Transform->X <= 1) {
		kill();
	}

	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
}

void SoulBullet::OnCollide(Character* source)
{
	if (source->GetName() == "player")
		kill();
}

void SoulBullet::AnimationState() {
	if (m_IsRunning) {
		m_Animation->SetProps("Soul_bullet", 1, 4, 150);
	}
}


