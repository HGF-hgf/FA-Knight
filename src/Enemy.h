#pragma once
#include"Character.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"


using namespace std;

#define VEL 1.5f
#define KNOCKBACKFORCE 5.0f 

class Enemy : public Character {
public:
	Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);

	virtual void Update(float dt);
	virtual void OnCollide(Character* source);
	void moveToPlayer(float dt);
	void autoMove();

	SDL_Rect GetSwordBox();
	void KnockBack(float dt);

private:
	void AnimationState();
	float m_Vision;
	float m_high;
	int HP = 3;
	bool m_beingHit = false;
	bool dead = false;
	int p;
};