#include"Camera.h"
#include"Engine.h"
using namespace std;

Camera* Camera::s_Instance = nullptr;

Camera::Camera() {
	m_ViewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //mo ta vi tri kich thuoc cua so game
}

void Camera::Update(float dt) {
	//ktra neu nvat ton tai thi theo doi 
	if (m_Target != nullptr ) {
		m_ViewBox.x = m_Target->X - SCREEN_WIDTH / 2;//set vi tri cua hop luon o giua nhan vat va o giua man hinh
		m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT / 2;

		if (m_ViewBox.x < 0) {
			m_ViewBox.x = 0;
		}							//ktra neu phan hop cam chay theo nguoi choi bien ra ngoai bien thi se gan chung bang 0 de cam ko bi vuot qua bien							
		if (m_ViewBox.y < 0) {
			m_ViewBox.y = 0;
		}

		/*if (m_ViewBox.x > (SCREEN_WIDTH * 2 - m_ViewBox.w)) {
			m_ViewBox.x = (SCREEN_WIDTH * 2 - m_ViewBox.w);
		}*/
		
		if (m_ViewBox.y > (SCREEN_HEIGHT - m_ViewBox.h)) {       // gioi han phan cam di chuyen theo y
			m_ViewBox.y = (SCREEN_HEIGHT - m_ViewBox.h);
		}

		m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y); // cap nhat vi tri cua camera
	}

}