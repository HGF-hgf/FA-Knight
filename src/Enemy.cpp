#include"Enemy.h"
#include"Texture.h"
#include"Input.h"
#include"Engine.h"
#include"Player.h"
#include"CollisionHandler.h"
#include"Camera.h"
#include"Game.h"

Enemy::Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) :Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;
}


void Enemy::Update(float dt) {	
	moveToPlayer();
	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
	
}

void Enemy::OnCollide(Character* source)
{
	if (source->GetName() == "bullet") {
		HP--;
		
	}
	if (HP == 0)
		m_beingHit = true;
}

void Enemy::AnimationState() {
	//idle
	m_Animation->SetProps("Enemy_idle", 1, 4, 170);
	//run 
	if (m_IsRunning && !m_IsAttacking)
		m_Animation->SetProps("Enemy_run", 1, 4, 150);
	//attack
	if (m_IsAttacking)
		m_Animation->SetProps("Enemy_attack", 1, 4, 150);
	//fall
	if (m_beingHit) {
		m_Animation->SetProps("Enemy_fall", 1, 4, 100);
		if (m_Animation->GetCurrentFrame() == 3)
			kill();
	}
	//beinghit
	//if(m_beingHit)
}

void Enemy::moveToPlayer() {
	m_IsRunning = false;
	m_IsAttacking = false;
	m_Rigidbody->UnsetForce();
	
	m_Vision = Game::Getinstance()->Getplayer()->GetX() - GetX();
	m_high = Game::Getinstance()->Getplayer()->GetY() - GetY();

	if (m_Vision <= 300 && m_Vision > 100) {
		m_Rigidbody->ApplyForceX(FORWARD * VEL);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;	
		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 1 || CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 4) {
			m_IsRunning = false;
			m_Rigidbody->UnsetForce();
		}
	}

	if (m_Vision >= -300 && m_Vision < -40) {
		m_Rigidbody->ApplyForceX(BACKWARD * VEL);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 2 || CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 3) {
			m_IsRunning = false;
			m_Rigidbody->UnsetForce();
		}
	}
	//cout << m_Transform->Y << " " << m_Transform->X << endl;
	
	if (m_Rigidbody->Velocity().Y > 0 && !m_IsGrounded) {
		m_IsFalling = true;
	}
	else {
		m_IsFalling = false;
	}

	if ((m_Vision >= -40 && m_Vision < 0) || (m_Vision <= 100 && m_Vision > 0)) {
		if (abs(m_high) < 100) {
			m_IsAttacking = true;
		}
		else m_Rigidbody->UnsetForce();
	}
	autoMove();
	//KnockBack();
}


void Enemy::autoMove() {
	if (abs(m_Vision) > 300 && !m_IsFalling) {

		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 1 || CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 4) {
			m_Flip = SDL_FLIP_HORIZONTAL;
		}

		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 2 || (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 3)){
			m_Flip = SDL_FLIP_NONE;
		}

		if (m_Flip == SDL_FLIP_HORIZONTAL && !m_IsAttacking) {
			m_Rigidbody->ApplyForceX(BACKWARD * VEL);
			m_IsRunning = true;
		}

		if (m_Flip == SDL_FLIP_NONE && !m_IsAttacking) {
			m_Rigidbody->ApplyForceX(FORWARD * VEL);
			m_IsRunning = true;
		}
	}          
}

SDL_Rect Enemy::GetSwordBox()
{
	float x = m_Transform->X;
	float y = m_Transform->Y;
	float w = 20;
	float h = 30;
	return SDL_Rect(x, y, w, h);
}