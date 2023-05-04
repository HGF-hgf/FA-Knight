#include"Tile.h"
#include"Texture.h"

using namespace std;

// nhan vao cac tham so de khoi tao Tile
Tile::Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
	: m_Tilesize(tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_TileMap(tilemap), m_Tilesets(tilesets) {
	
	// tai cac tep texture cho cac Tileset duoc su trong map voi moi tileset thi ham LoadTexture duoc goi de tai texture tu duong dan va ten cua file nguon Tileset
	for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
		Texture::Getinstance()->LoadTexture(m_Tilesets[i].Name, "texture/map/" + m_Tilesets[i].Source);
	}

}


// ve ban do len man hinh
void Tile::Render() {

	// vong lap de duyet cac hang va cot cua ban do
	for (unsigned int i = 0;i < m_RowCount;i++) {
		for (unsigned int j = 0; j < m_ColCount;j++) {
			int tileID = m_TileMap[i][j];
			//int temp = tileID;

			if (tileID == 0) // neu bang 0 thi bo qua tile nay va tiep tuc
				continue;
			else {
				int index = 0 ;
				// bat dau xet neu size cua m_Tilesets > 0 
				if (m_Tilesets.size() > 1) {
					// duyet tung tileset trong danh sach de tim ra tileset chua tile dang xet
					for (unsigned int k = 1; k < m_Tilesets.size();k++) {
						//ktra bang cach check xem tileID co nam trong khoang tu FirstID den LastID cua tileset k
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID) {
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID; // tinh lai tileID bang cach cong them so luong tile cua tileset tru di LastID
							index = k; // cap nhat index de luu 
							break;
						}
					}
				}

				Tileset ts = m_Tilesets[index]; // lay tileset tuong ung 
				int tileRow = tileID / ts.ColCount; // tinh so dong cua tile
				int tileCol = tileID - tileRow * ts.ColCount - 1; // tinh so cot cua tile

				// neu tile dang xet nam o cot cuoi cua moi hang tileRow se bi giam di va tileCol se gan bang gia tri cot cuoi cung
				if (tileID % ts.ColCount == 0) {
					tileRow--;
					tileCol = ts.ColCount - 1;
				}
				Texture::Getinstance()->DrawTile(ts.Name, ts.Tilesize, j * ts.Tilesize, i * ts.Tilesize, tileRow, tileCol); // ve tile
			}
		}
	}
}

void Tile::Update() {

}