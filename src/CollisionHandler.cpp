#include "CollisionHandler.h"
#include"Engine.h"
#include"Game.h"

using namespace std;

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (Tile*)Game::Getinstance()->GetMap()->GetLayers().back();
	m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

// ham su dung de check xem hai hcn co dang chong len nhau k
bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overLaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overLaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overLaps && y_overLaps);
}

int CollisionHandler::checkTileID(SDL_Rect a) {
	int tileSize = 32;
	int RowCount = 1000;
	int ColCount = 5000;

	int left_tile = a.x / tileSize;	//lay thu tu o ben trai
	int right_tile = (a.x + a.w) / tileSize; // lay thu tu o ben phai

	int top_tile = a.y / tileSize; // lay thu tu o tren
	int bottom_tile = (a.y + a.h) / tileSize; // lay thu tu o duoi chan

	// neu cac gia tri ra khoi gioi han thi gan chung bang gia tri hop le gan nhat
	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	// ktra cac o giao nhau neu lon hon 0 thi tra ve gia tri o duoi
	for (int i = left_tile; i <= right_tile; ++i) {
		for (int j = top_tile; j <= bottom_tile; ++j) {
			if (m_CollisionTilemap[j][i] > 0) {
				return m_CollisionTilemap[j][i];
			}
		}
	}
	return 0;
}

// tuong tu ham tren nhung tra ve dung neu m_CollisionTilemap[j][i] > 0
bool CollisionHandler::MapCollision(SDL_Rect a) {
	if (checkTileID(a) > 0) {
		return true;
	}
	else return false;
}

float CollisionHandler::checkNextTile(SDL_Rect a) {
	int tileSize = 32;
	int RowCount = 1000;
	int ColCount = 8000;

	int left_tile = a.x / tileSize;	//lay thu tu o ben trai
	int right_tile = (a.x + a.w) / tileSize; // lay thu tu o ben phai

	int top_tile = a.y / tileSize; // lay thu tu o tren
	int bottom_tile = (a.y + a.h) / tileSize; // lay thu tu o duoi chan

	// neu cac gia tri ra khoi gioi han thi gan chung bang gia tri hop le gan nhat
	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	// ktra cac o giao nhau neu lon hon 0 thi tra ve gia tri o duoi
	for (int i = left_tile; i <= right_tile; ++i) {
		for (int j = top_tile; j <= bottom_tile; ++j) {
			if (m_CollisionTilemap[j][i] > 0){
				if (m_CollisionTilemap[j][i + 1] == 0)
					return 1;
				if (m_CollisionTilemap[j][i - 1] == 0)
					return 2;
				if (m_CollisionTilemap[j - 1][i - 1] != 0 || m_CollisionTilemap[j - 2][i - 1] != 0 || m_CollisionTilemap[j - 3][i - 1] != 0 || (m_CollisionTilemap[j - 1][i - 1] != 0 && m_CollisionTilemap[j - 2][i - 1] != 0) || (m_CollisionTilemap[j - 1][i - 1] != 0 && m_CollisionTilemap[j - 3][i - 1] != 0) || (m_CollisionTilemap[j - 1][i - 1] != 0 && m_CollisionTilemap[j - 2][i - 1] != 0 && m_CollisionTilemap[j - 3][i - 1] != 0) || (m_CollisionTilemap[j - 2][i - 1] != 0 && m_CollisionTilemap[j - 3][i - 1] != 0))
					return 3;
				if (m_CollisionTilemap[j - 1][i + 1] != 0 || m_CollisionTilemap[j - 2][i + 1] != 0 || m_CollisionTilemap[j - 3][i + 1] != 0 || (m_CollisionTilemap[j - 1][i + 1] != 0 && m_CollisionTilemap[j - 2][i + 1] != 0) || (m_CollisionTilemap[j - 1][i + 1] != 0 && m_CollisionTilemap[j - 3][i + 1] != 0) || (m_CollisionTilemap[j - 1][i + 1] != 0 && m_CollisionTilemap[j - 2][i + 1] != 0 && m_CollisionTilemap[j - 3][i + 1] != 0) || (m_CollisionTilemap[j - 2][i + 1] != 0 && m_CollisionTilemap[j - 3][i + 1] != 0))
					return 4;	
			}
		}
	}
	return 0;
}