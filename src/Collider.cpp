#include"Collider.h"
#include"Engine.h"
//ham ve hop ktra va cham
void  Collider::Draw() {
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = { (int)(m_Box.x - cam.X), (int)(m_Box.y - cam.Y), m_Box.w,  m_Box.h };
	SDL_RenderDrawRect(Engine::Getinstance()->GetRenderer(), &box);
}