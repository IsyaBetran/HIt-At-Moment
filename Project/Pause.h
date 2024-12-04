#ifndef PAUSE_H
#define PAUSE_H

#include "Screen.h"
#include "Setting.h"
#include "GameData.h"
#include "Texture.h"
#include "Sprite.h"
#include "Input.h"
#include "ScreenManager.h"

namespace Engine {
	class Pause :
		public Engine::Screen
	{
	public:
		Pause(Setting* set) : dataManager(GameData::getInstance()) { setting = set; }
		~Pause();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		GameData& dataManager;
		Setting* setting;
		Sprite* tombol[3];
		int currentTombol = 0;
	};
}
#endif
