#include "Texture.h"
#include"Engine.h"
#include"Camera.h"

using namespace std;

Texture* Texture::s_Instance = nullptr;

// ham dung de tai hinh anh tu file va luu vao map m_TextureMap voi key la id cua hinh anh
bool Texture::LoadTexture(string id, string filename) {
	SDL_Surface* surface = IMG_Load((RESOURCE_PATH + filename).c_str());
	if (surface == nullptr) {
		SDL_Log("FAILED TO LOAD TEXTURE\n", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Getinstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("FAILED TO CREATE TEXTURE FROM SURFACE\n", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;
	return true;
}

//ham de ve hinh anh tu m_TextureMap voi key la id tai vi tri (x,y) va tinh toan vi tri cua camera  
void Texture::Draw(string id, int x, int y, int width, int height,float Xscale, float Yscale ,float scrollRatio, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0, 0, width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;
	SDL_Rect dstRect = { x - cam.X,y - cam.Y,width * Xscale,height * Yscale };
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);// copy lai phan vua ve theo thoi gian dua theo cac yeu to tren
}

//ham de ve cac o tu mot map voi id cho truoc viec chon o can ve duoc xac dinh bang hai gia tri la p_row va p_frame
void Texture::DrawTile(string p_id, int p_tilesize, int p_x, int p_y, int p_row, int p_frame, SDL_RendererFlip p_flip)
{
	SDL_Rect srcRect = { p_tilesize * p_frame, p_tilesize* p_row, p_tilesize, p_tilesize };//xac dinh o can ve
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { p_x - cam.X, p_y - cam.Y , p_tilesize, p_tilesize };// vi tri cua o do
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[p_id], &srcRect, &dstRect, 0, nullptr, p_flip);
}

//ham dung de ve frame 
void Texture::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width * frame, height * (row - 1), width,height };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X,y - cam.Y,width,height };
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

//dung de doc thong tin tu file XML, tim phan tu co ten texture va goi ham LoadTexture de tai hinh anh tu cac phan da duoc luu trong file XML
bool Texture::ParseTexture(string source) {
	 
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		cout << "FAILED TO LOAD" << endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == string("texture")) {
			string id = e->Attribute("id");
			string src = e->Attribute("source");
			LoadTexture(id, src);
		}
	}
	cout << "LOADED" << endl;
	return true;
}

//de giai phong bo nho cua 1 hinh duoc luu tru trong m_TextureMap
void Texture::Drop(string id) {
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

//nhhu ham tren nhung la toan bo phan duoc luu trong m_TextureMap
void Texture::Clean() {
	map<string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	m_TextureMap.clear();
	
}

