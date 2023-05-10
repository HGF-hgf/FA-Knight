#include"Player.h"
#include"Texture.h"
#include"Input.h"
#include"Engine.h"
#include"CollisionHandler.h"
#include"Camera.h"
#include"Bullet.h"
#include"Game.h"


Player::Player(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	
	//m_RunForce = RUN_FORCE;
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;
	m_lastAttack = 0;
}

void Player::Update(float dt) {
	idle = true;
	m_IsRunning = false;
	m_IsDead = false;
	m_IsAttacking = false;
	m_Rigidbody->UnsetForce();

	int x, y;
	
	if (m_Flip == SDL_FLIP_NONE) {
		x = m_Transform->X + 60;
		y = m_Transform->Y + 44;
		
	}

	if (m_Flip == SDL_FLIP_HORIZONTAL) {
		x = m_Transform->X;
		y = m_Transform->Y + 44;
		
	}
	//cout << GetX() << " " << GetY() << endl; //159 413 // 3010 607


	//RUN FORWARD
	if (!m_BeingHit) {
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD) {
			m_Rigidbody->ApplyForceX(FORWARD * RUN_FORCE);
			m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
			idle = false;
		}

		//RUN BACKWARD
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD) {
			m_Rigidbody->ApplyForceX(BACKWARD * RUN_FORCE);
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_IsRunning = true;
			idle = false;
		}

		//ATTACK
		int currentTick = SDL_GetTicks();

		if (Input::GetInstance()->GetAxisKey(ATTACK) == 1 && currentTick - m_lastAttack > ATTACK_TIME) {
			m_Rigidbody->UnsetForce();
			m_IsAttacking = true;
			idle = false;
			Bullet* bullet = new Bullet(new Properties("bullet", x, y, 64, 64), 1, 2, 100, -42, -39, 16, 16);
			Game::Getinstance()->addCharacter(bullet);
			bullet->GetFlipType(m_Flip);
			Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[2], 0);
			m_lastAttack = currentTick;
		}

		//JUMP
		if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARD && m_IsGrounded) {
			m_IsJumping = true;
			m_IsGrounded = false;
			m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
			Mix_PlayChannel(-1, Engine::Getinstance()->m_sfx[0], 0);
			idle = false;
		}

		if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARD && m_IsJumping && m_JumpTime > 0) {
			m_JumpTime -= dt;
			m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
		}
		else
		{
			m_IsJumping = false;
			m_JumpTime = JUMP_TIME;
		}

		//FALL
		if (m_Rigidbody->Velocity().Y > 0 && !m_IsGrounded) {
			m_IsFalling = true;
			idle = false;
		}
		else {
			m_IsFalling = false;
		}

		//ATTACK TIMER 
		if (m_IsAttacking && m_AttackTime > 0) {
			m_AttackTime -= dt;
		}
		else {
			m_IsAttacking = false;
			m_AttackTime = ATTACK_TIME;
		}
	}

	Character::Update(dt);	
	AnimationState();
	m_Animation->Update(dt);

	if (GetY() >= 647) {
		dead = true;
	}
	if (CollisionHandler::GetInstance()->checkTileID(m_Collider->Get()) == 231 || CollisionHandler::GetInstance()->checkTileID(m_Collider->Get()) == 240 || CollisionHandler::GetInstance()->checkTileID(m_Collider->Get()) == 255 || CollisionHandler::GetInstance()->checkTileID(m_Collider->Get()) == 261) {
		m_BeingHit = true;
	}
}

void Player::OnCollide(Character* source)
{
	if (source->GetName() == "soulbullet") {
		m_BeingHit = true;
	}
	if (source->GetName() == "portal1") {
		m_Transform->X = 4200;
		m_Transform->Y = 100;
		Mix_PlayMusic(Engine::Getinstance()->m_music[4], -1);
	}
	if (source->GetName() == "portal2") {
		m_Transform->X = 8934;
		m_Transform->Y = 222;
		Mix_PlayMusic(Engine::Getinstance()->m_music[5], -1);
	}
	if (source->GetName() == "portal3") {
		Game::Getinstance()->m_Ended = true;
		m_Transform->X = 13280;
		m_Transform->Y = 222;
		Mix_PlayMusic(Engine::Getinstance()->m_music[6], -1);
		
	}
}

void Player::AnimationState() {
	//idle
	if (m_BeingHit) {
		m_Animation->SetProps("player_death", 1, 4, 300);
		if (m_Animation->GetCurrentFrame() == 3)
			dead = true;
	}
	else
		if (m_IsJumping)
			m_Animation->SetProps("player_jump", 1, 3, 250);
		else
			if (m_IsFalling)
				m_Animation->SetProps("player_fall", 1, 3, 450);
			else
				if (m_IsAttacking)
					m_Animation->SetProps("player_attack", 1, 3, 50);
				else
					if (m_IsRunning)
						m_Animation->SetProps("player_run", 1, 4, 150);
					else
						m_Animation->SetProps("player_idle", 1, 6, 100);

}