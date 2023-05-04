//#pragma once
//#include<map>
//#include<string>
//#include<vector>
//#include<SDL.h>
//#include"Animation.h"
//
//using namespace std;
//
//struct Sequence {
//	int Speed;
//	int FrameCount;
//	int Width, Height;
//	std::vector<std::string> TextureIDs; 
//};
//
//class SeqAnimation: public Animation
//{
//public:
//	SeqAnimation(bool repeat = true);
//
//	virtual void Update(float dt);
//	void Parse(string source);
//	void SetCurrentSeq(string seqID);
//	void SetRepeat(bool repeat) { m_Repeat = repeat; }
//	void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
//
//private:
//	Sequence m_CurrentSeq; // player state
//	std::map<std::string, Sequence> m_SeqMap;
//};
//
