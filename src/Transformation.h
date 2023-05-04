#pragma once

#include"Vector2D.h"
using namespace std;

class Transform{
public:
	float X, Y;
public:
	Transform(float x = 0, float y = 0) : X(x), Y(y){}
	void Log(string mag = "") {
		cout << mag << "(X,Y) = (" << X << " " << Y << ")" << endl;
	}
public:
	inline void TransformX(float x) { X += x; }
	inline void TransformY(float y) { Y += y; }
	inline void TransformV(Vector2D v) { X += v.X; Y += v.Y; }
};