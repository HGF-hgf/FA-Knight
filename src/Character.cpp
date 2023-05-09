

#include"Character.h"
#include"Texture.h"
#include"Input.h"
#include"Engine.h"

#include"CollisionHandler.h"
#include"Camera.h"

Character::Character(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : GameObject(props) {

	m_Name = props->TextureID;
	m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsDead = false;
	m_BeingHit = false;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	m_Collider->SetBuffer(x, y, w, h);

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(3.0f);

	m_Animation = new SpriteAnimation();
	m_Animation->SetProps(m_TextureID, Row, FrameCount, AnimationSpeed);

}

void Character::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_width, m_height, 1, 1, m_Flip);
	//m_Collider->Draw();
}

void Character::Update(float dt) {

	//move on X axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_Rigidbody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 0, 0);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
		m_Transform->X = m_LastSafePosition.X;

	//move on Y axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_Rigidbody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 0, 0);//+44 +32 30 63

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_width / 2;
	m_Origin->Y = m_Transform->Y + m_height / 2;
	
	//m_Animation->Update(dt);
}


void Character::Clean() {
	Texture::Getinstance()->Drop(m_TextureID);
}

void Character::OnCollide(Character* target)
{
}

void Character::kill()
{
	m_IsDead = true;
}

bool Character::IsDead() const
{
	return m_IsDead;
}

std::string Character::GetName() const
{
	return m_Name;
}

float Character::GetX() {
	return m_Transform->X;
}

float Character::GetY() {
	return m_Transform->Y;
}




SDL_Rect Character::GetBox()
{
	return m_Collider->Get();
}
