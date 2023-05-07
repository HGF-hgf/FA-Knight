#include"Soul.h"
#include"Texture.h"
#include"Input.h"
#include"Engine.h"
#include"Player.h"
#include"CollisionHandler.h"
#include"Camera.h"
#include"SoulBullet.h"
#include"Game.h"
Soul::Soul(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) :Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;
	m_lastAttack = 0;
}


void Soul::Update(float dt) {
	moveToPlayer();
	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
}

void Soul::OnCollide(Character* source)
{
	if (source->GetName() == "bullet") {
		HP--;
		
	}
	if (HP == 0)
		m_beingHit = true;
}

void Soul::AnimationState() {
	int x, y;

	if (m_Flip == SDL_FLIP_NONE) {
		x = m_Transform->X+30;
		y = m_Transform->Y + 3;

	}

	if (m_Flip == SDL_FLIP_HORIZONTAL) {
		x = m_Transform->X-30;
		y = m_Transform->Y + 3;

	}
	//idle
	m_Animation->SetProps("Soul_idle", 1, 5, 170);
	//run 
	if (m_IsRunning && !m_IsAttacking)
		m_Animation->SetProps("Soul_move", 1, 8, 150);
	//attack
	int currentTick = SDL_GetTicks();
	if (m_IsAttacking) {
		m_Animation->SetProps("Soul_attack", 1, 10, 150);

		if (m_Animation->GetCurrentFrame() == 6 && currentTick - m_lastAttack > S_ATTACK_TIME)
		{
			SoulBullet* soulbullet = new SoulBullet(new Properties("soulbullet", x, y, 128, 128), 1, 4, 100, -75, -74, 20, 20);
			Game::Getinstance()->addCharacter(soulbullet);
			soulbullet->GetFlipType(m_Flip);
			m_lastAttack = currentTick;
		}
		if (m_Animation->GetCurrentFrame() == 9)
			m_IsAttacking = false;
	}
	//fall
	/*if (m_IsFalling)
		m_Animation->SetProps("Soul_fall", 1, 4, 150);*/
	//beingHit
	if (m_beingHit) {
		m_Animation->SetProps("Soul_death", 1, 8, 250);
		if (m_Animation->GetCurrentFrame() == 7) {
			kill();
			Game::Getinstance()->m_Score += 1;
		}
	}
}


void Soul::moveToPlayer() {
	m_IsRunning = false;
	//m_IsAttacking = false;
	m_Rigidbody->UnsetForce();

	

	m_Vision = Game::Getinstance()->Getplayer()->GetX() - GetX();
	m_high = Game::Getinstance()->Getplayer()->GetY() - GetY();

	if (m_Vision <= 300 && m_Vision > 0) {
		m_Rigidbody->ApplyForceX(FORWARD * VEL);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 1 || CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 4) {
			m_IsRunning = false;
			m_Rigidbody->UnsetForce();
		}
	}

	if (m_Vision >= -300 && m_Vision < 0) {
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

	//Attack
	
	if (((m_Vision >= -200 && m_Vision < 5) || (m_Vision <= 200 && m_Vision > 5)) ) {
		m_Rigidbody->UnsetForce();
		m_IsAttacking = true;
		
	}

	/*if ((m_Vision >= -200 && m_Vision < 0) || (m_Vision <= 200 && m_Vision > 0)) {
		if (abs(m_high) < 100) {
			m_IsAttacking = true;
		}
		else m_Rigidbody->UnsetForce();
	}*/
	autoMove();
	//KnockBack();
}


void Soul::autoMove() {
	if (abs(m_Vision) > 300 && !m_IsFalling) {

		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 1 || CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 4) {
			m_Flip = SDL_FLIP_HORIZONTAL;
		}

		if (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 2 || (CollisionHandler::GetInstance()->checkNextTile(m_Collider->Get()) == 3)) {
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