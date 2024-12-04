#ifndef ENDSCOREDISPLAY_H
#define ENDSCOREDISPLAY_H

#include "Screen.h"
#include "Setting.h"
#include "GameData.h"
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "Input.h"
#include "ScreenManager.h"

namespace Engine {
	class EndScoreDisplay :
		public Engine::Screen
	{
	public:
		EndScoreDisplay(Setting* set) : dataManager(GameData::getInstance()) { setting = set;}
		~EndScoreDisplay();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		GameData& dataManager;
		Setting* setting;
		Input* inputManager;
		Sprite* bg;
		Sprite* enterButton;
		Sprite* characterSprite;
		Text* tierText;
		Text* scoreText;
		Text* scoreNumber;
		bool timerOn = false;
		float timer = 3;
	};
}
#endif
