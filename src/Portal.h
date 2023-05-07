#pragma once
#include"Character.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"


using namespace std;

class Portal : public Character {
public:
	Portal(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);

	virtual void Update(float dt);
	/*virtual void OnCollide(Character* source);
	*/

	//void KnockBack();

private:
	void AnimationState();
	
};