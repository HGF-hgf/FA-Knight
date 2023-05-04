#pragma once
using namespace std;


/*class Animation {
//public:
//	Animation(bool repeat = true) : m_Repeat(repeat) { m_IsEnded = false; }
//	
//	virtual void Update()  ;
//	inline bool IsEnded() { return m_IsEnded; }
//	void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
//	void SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed);
//
//private:
//	int m_spriteRow, m_spriteFrame;
//	int m_AnimationSpeed, m_FrameCount;
//	string m_textureID;
//	//SDL_RendererFlip m_Flip;
//	int m_CurrentFrame;
//	bool m_Repeat;
//	bool m_IsEnded;
};*/

class Animation {

public:
    Animation(bool repeat = true): m_Repeat(repeat) { m_IsEnded = false; }

    virtual void Update(float dt) = 0;
    inline bool IsEnded() { return m_IsEnded; }

protected:
    bool m_Repeat;
    bool m_IsEnded;
    int m_CurrentFrame;
};