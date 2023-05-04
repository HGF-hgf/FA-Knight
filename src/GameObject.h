#pragma once
#include"Object.h"
#include"Point.h"
#include"Transformation.h"


using namespace std;

struct Properties
{
public:
	// ham chua thuoc tinh cua character
	Properties(string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Height = height;
		TextureID = textureID;
	}
public:
	string TextureID;
	int Width, Height;
	float X, Y;
	SDL_RendererFlip Flip;
};

class GameObject : public Object
{
public:
	GameObject(Properties* props)  
	:m_TextureID(props->TextureID), m_width(props->Width), m_height(props->Height), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);
		
		float px = (props->X + props->Width) / 2;
		float py = (props->Y + props->Height) / 2;
		m_Origin = new Point(px, py);


		m_Id = s_N;
		s_N++;
	}
	int GetId() const
	{
		return m_Id;
	}

	inline Point* GetOrigin() { return m_Origin; } // tra ve toa do tam cua character

	//virtual ~GameObject() {}
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	Point* m_Origin;
	Transform* m_Transform;
	int m_width, m_height;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
	int m_Id;
	static int s_N;
};
