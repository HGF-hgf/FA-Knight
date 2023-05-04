#pragma once

const int FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
public:
	inline float GetDeltaTime() { return m_DeltaTime; }
	inline static Timer* Getinstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }
	void Tick();

private:
	Timer(){};
	static Timer* s_Instance;
	float m_DeltaTime;
	float m_LastTime;

};