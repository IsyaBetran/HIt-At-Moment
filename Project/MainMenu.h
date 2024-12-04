#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.h"
#include "Setting.h"
#include "GameData.h"
#include "Texture.h"	
#include "Sprite.h"
#include "Text.h"
#include "Input.h"
#include "ScreenManager.h"
#include "HighScoreManager.h"
#include <vector>

namespace Engine {
	class MainMenu :
		public Engine::Screen
	{
	public:
		MainMenu(Setting* set) : dataManager(GameData::getInstance()) { setting = set; }
		~MainMenu();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		GameData& dataManager;
		HighScoreManager* scoremanager = new HighScoreManager("MusicHighScore.txt");
		Setting* setting;
		Sprite* bg;
		Sprite* enterExit;
		Sprite* gameIcon[2];
		Text* score1;
		Text* score2;
		Text* score3;
		Text* score4;
		Text* score5;

		bool isChangeIconLeft = false;
		bool isChangeIconRight = false;
		int currentButtonIndex = 0;
		string nameGame[1] = {"Music1"};
		vector<int> highScorer;

		void ChangeIconLeft(float deltaTime);
		void ChangeIconRight(float deltaTime);
	};
}
#endif
