#pragma once
#include"Character.h"
#include"Bullet.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"
#include"Enemy.h"

#define JUMP_TIME 2.0f
#define JUMP_FORCE 7.0f

#define RUN_FORCE 3.0f
#define ATTACK_TIME 500 // ms
using namespace std;
 
class Player : public Character {
public:
	Player(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);
	

	virtual void Update(float dt);
	virtual void OnCollide(Character* source);

	
private:
	friend class Game;
	friend class Engine;
	void AnimationState();
	float m_Vision;
	int m_lastAttack;
	
	bool dead = false;
	bool idle;
};