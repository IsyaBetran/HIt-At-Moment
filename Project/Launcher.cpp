#include "Setting.h"
#include "Game.h"

#include "GameManager.h"

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 1920;
	setting->screenHeight = 1080;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 75;
	Engine::Game* game = new Engine::GameManager(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
