#ifndef COLLISIONHANDLE_H
#define COLLISIONHANDLE_H





#include"Tile.h"
#include"Map.h"
//#include"Engine.h"

class CollisionHandler
{
public:
	bool MapCollision(SDL_Rect a);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	int checkTileID(SDL_Rect a);
	float checkNextTile(SDL_Rect a);
	bool check(SDL_Rect a);
	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
	CollisionHandler();
	TileMap m_CollisionTilemap;
	Tile* m_CollisionLayer;
	static CollisionHandler* s_Instance;
};
#endif // !1