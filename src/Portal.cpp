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
	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
}

void Portal::AnimationState()
{
	m_Animation->SetProps("portal1", 1, 9, 150);
}


