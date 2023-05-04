#include"Timer.h"

Timer* Timer::s_Instance = nullptr;

// ham tinh thoi gian giua cac frame
void Timer::Tick() {
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (FPS / 10000.0f); // tinh thoi gian ke tu lan goi ham trc 
	
	// neu m_DeltaTime lon hon thi gan bang TARGET_DELTATIME de tranh viec loi hien thi frame
	if (m_DeltaTime > TARGET_DELTATIME)
		m_DeltaTime = TARGET_DELTATIME;
	m_LastTime = SDL_GetTicks();
}