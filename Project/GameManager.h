#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Game.h"
#include "Setting.h"
#include "ScreenManager.h"
#include "FirstMusic.h"	
#include "EndScoreDisplay.h"
#include "MainMenu.h"
#include "Pause.h"
#include "SplashScreen.h"

namespace Engine {
	class GameManager :public Engine::Game
	{
	public:
		GameManager(Setting* setting);
		~GameManager();
		virtual void Init();
		virtual void Update();
		virtual void Render();

	};
}

#endif

