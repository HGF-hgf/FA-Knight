#include"Texture.h"
#include"Input.h"
#include"Engine.h"
#include"Player.h"
#include"CollisionHandler.h"
#include"Camera.h"
#include"Game.h"
#include"Portal.h"

Portal::Portal(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h){
	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(0.0f);
}

void Portal::Update(float dt)
{
	//7044 /479
	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
}

void Portal::AnimationState()
{
	if (GetX() == 2300)
		m_Animation->SetProps("portal1", 1, 8, 150);
	if (GetX() == 7000)
		m_Animation->SetProps("portal2", 1, 9, 150);
	if (GetX() == 11841)
		m_Animation->SetProps("portal3", 1, 8, 150);

	for (int i = 0;i < size(Game::Getinstance()->m_x);++i) {
		if (GetX() == Game::Getinstance()->m_x[i]) {
			m_Animation->SetProps("lazer", 1, 18, 70);
			if (m_Animation->GetCurrentFrame() <= 9 && m_Animation->GetCurrentFrame() > 3 && CollisionHandler::GetInstance()->checkCollision(Game::Getinstance()->Getplayer()->GetBox(), m_Collider->Get()))
				Game::Getinstance()->Getplayer()->m_BeingHit = true;
		}
	}

	for (int i = 0; i < 4;++i) {
		if (GetX() == 10600 + 192 * i) {
			m_Animation->SetProps("hammer", 1, 8, 180);
			if ((m_Animation->GetCurrentFrame() >= 1 && m_Animation->GetCurrentFrame() <= 4) && CollisionHandler::GetInstance()->checkCollision(Game::Getinstance()->Getplayer()->GetBox(), m_Collider->Get())) {
				Game::Getinstance()->Getplayer()->m_BeingHit = true;
			}
		}
	}
}


