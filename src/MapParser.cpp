#include"MapParser.h"

using namespace std;

MapParser* MapParser::s_Instance = nullptr;

//ktra map co dc load ko
bool MapParser::Load() {
	if(!Parse("Level1", RESOURCE_PATH + "texture/map/map1.tmx"))
		return false;
	if (!Parse("Level2", RESOURCE_PATH + "texture/map/map2.tmx"))
		return false;
	return true;
	
}


// ham nhan vao id va duong dan tep
bool MapParser::Parse(string id, string source) {
	TiXmlDocument xml; 
	xml.LoadFile(source);
	//ktra xem tep dang xet co duoc tai ko 
	if (xml.Error()) {
		cerr << "Failed to load" << source << endl;
		return false;
	}


	TiXmlElement* root = xml.RootElement();
	int rowcount, colcount, tilesize = 0;
	root->Attribute("width", &colcount); // so cot cua map
	root->Attribute("height", &rowcount); // so hang cua map 
	root->Attribute("tilewidth", &tilesize); // size cua mot o trong map


	
	TilesetList tilesets;
	// loop nay dung de ktra tat ca cac phan tu cua tileset va luu vao tilesets
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	
	Map* gamemap = new Map();
	// xet voi moi layer su dung ham parsetilelayer de phan tich layer tren map va luu vao maplayer
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == string("layer")) {
			Tile* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayer.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap; // luu gamemap vao dua tren id cua map
	return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	//lay cac thong tin tu file tmx
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.Tilesize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;

}

Tile* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
	TiXmlElement* data = nullptr;
	// duyet de tim "data"
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("data")) {
			data = e;
			break;
		}
	}

	string matrix(data->GetText()); // lay cac phan tu thuoc data duoi dang string
	istringstream iss(matrix); // chuyen chuoi nay thanh cac so nguyen 
	string id;

	TileMap tilemap(rowcount, vector<int>(colcount, 0));

	for (int row = 0; row < rowcount; row++) {
		for (int col = 0; col < colcount; col++) {
			getline(iss, id, ','); // lay gia tri cac tile r luu vao id
			stringstream convertor(id);
			convertor >> tilemap[row][col];// luu vao o tuong ung 

			if (!iss.good()) // ket thuc vong lap khi khong con gia tri de doc
				break;
		}
	}

	return (new Tile(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean() {
	//xoa map vs key tuong ung
	map<string, Map*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end();it++)
		it->second = nullptr;

	m_MapDict.clear();
}