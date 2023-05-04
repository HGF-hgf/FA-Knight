#pragma once

#include"GameObject.h"

#include"Collider.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"

using namespace std;



class Character : public GameObject {
public:
	Character(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);
	

	virtual void Draw() ;
	virtual void Update(float dt) ;
	virtual void Clean();
	virtual void OnCollide(Character* target);

	void kill();

	bool IsDead() const;

	std::string GetName() const;

	float GetX();
	float GetY();

	SDL_Rect GetBox();

protected:
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_IsRunning;
	bool m_IsFalling;
	bool m_IsAttacking;
	bool m_IsDead;

	float m_RunForce;
	float m_JumpTime; // Time the Enemy leave the ground
	float m_JumpForce; //forcce apply on the Enemy at the jumpoing time
	float m_AttackTime;
	string m_Name;
	
	

	Collider* m_Collider;
	SpriteAnimation* m_Animation;
	Rigidbody* m_Rigidbody;
	Vector2D m_LastSafePosition;// to make sure the player doesn't stuck
 };