#pragma once


#include"Map.h"

#include"Tile.h"
#include"tinyxml.h"


using namespace std;
class MapParser {
public:
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }
	inline Map* GetMap(string id) { return m_MapDict[id]; }

	bool Load();
	void Clean();

private:
	MapParser() {}
	bool Parse(string id, string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	Tile* ParseTileLayer(TiXmlElement* xmlLayer, vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);
	
	static MapParser* s_Instance;
	map<string, Map*> m_MapDict;
};