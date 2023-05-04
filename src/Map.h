#pragma once

#include"Layer.h"


using namespace std;

class Map {
public:

	Map() {}

	void Render() {
		for (unsigned int i = 0; i < m_MapLayer.size();i++)
			m_MapLayer[i]->Render();
	}
	void Update() {
		for (unsigned int i = 0; i < m_MapLayer.size();i++)
			m_MapLayer[i]->Update();
	}
	vector<Layer*> GetLayers() { 
		return m_MapLayer;
	}
private:
	friend class MapParser;
	vector<Layer*> m_MapLayer;
};