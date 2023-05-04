#pragma once

#include"Layer.h"


using namespace std;

struct Tileset {
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, Tilesize;
	string Name, Source;
};

using TilesetList = vector<Tileset>;
using TileMap = vector<vector<int>>;

class Tile : public Layer {
public:
	Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
	virtual void Render() ;
	virtual void Update() ;
	inline TileMap GetTilemap() { return m_TileMap; }


private:
	int m_Tilesize;
	int m_RowCount, m_ColCount;
	TileMap m_TileMap;
	TilesetList m_Tilesets;
};