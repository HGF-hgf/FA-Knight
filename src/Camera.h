#pragma once
#include"Vector2D.h"
//#include"Engine.h"
#include"Point.h"
using namespace std;

class Camera {
public:
	
	void Update(float dt);

	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();}
	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }

private:

	Camera();

	SDL_Rect m_ViewBox;
	Point* m_Target;
	Vector2D m_Position;
	static Camera* s_Instance;
};