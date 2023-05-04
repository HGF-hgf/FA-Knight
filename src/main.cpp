#include"Engine.h"
#include"Timer.h"


int main(int argc, char** argv) {

	Engine::Getinstance()->Init();

	while (Engine::Getinstance()->isRunning()) {
		Engine::Getinstance()->Events(); //  kiem tra thao tac cua nguoi choi
		Engine::Getinstance()->Update(); // cap nhat trang thai game dua tren thao tac
		Engine::Getinstance()->Render(); // dua ra man hinh cac thay doi
		Timer::Getinstance()->Tick();
	}

	Engine::Getinstance()->Clean(); // clean tat ca khi nguoi choi thoat game
	//Engine::Getinstance()->Quit();
	return 0;
}
