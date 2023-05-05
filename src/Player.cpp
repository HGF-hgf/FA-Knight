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

	if (m_Transform->X >= 500) {
		Engine::Getinstance()->ChangeLv = true;
	}

	//RUN FORWARD
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
	else{
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


	Character::Update(dt);	
	AnimationState();
	m_Animation->Update(dt);
	if (GetY() >= 570) {
		dead = true;
	}
	//cout << dead << endl;
}

void Player::OnCollide(Character* source)
{
	/*if (source->GetName() == "enemy") {
		dead = true;
	}*/
}

void Player::AnimationState() {
	//idle
	if(idle)
		m_Animation->SetProps("player_idle", 1, 6, 100);

	//run
	if (m_IsRunning && !m_IsJumping)
		m_Animation->SetProps("player_run", 1, 4, 150);

	//jump
	if (m_IsJumping)
		m_Animation->SetProps("player_jump", 1, 3, 250);

	//falling
	if (m_IsFalling)
		m_Animation->SetProps("player_fall", 1, 3, 450);
	//dead
	/*if (dead && !m_IsAttacking && !m_IsRunning && !m_IsFalling && !m_IsJumping && !idle)
		m_Animation->SetProps("player_death", 1, 4, 200);*/
	//attack
	if (m_IsAttacking)
		m_Animation->SetProps("player_attack", 1, 3, 50);

}