#include "Bullet.h"
#include "Input.h"
#include "Player.h"
#include "Engine.h"

Bullet::Bullet(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(0.0f);
	m_IsRunning = true;
	m_tick = SDL_GetTicks();
}

void Bullet::Update(float dt) {
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

void Bullet::OnCollide(Character* source)
{
	if (source->GetName() == "enemy" || source->GetName() == "soul") {
		Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[3], 0);
		kill();	
	}
}

void Bullet::AnimationState() {
	if (m_IsRunning) {
		m_Animation->SetProps("bullet", 1, 2, 100);
	}
}


