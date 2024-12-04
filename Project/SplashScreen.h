#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Texture.h"
#include "Sprite.h"
#include "ScreenManager.h"

namespace Engine {
	class SplashScreen :
		public Engine::Screen
	{
	public:
		~SplashScreen();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		Sprite* logo;
		float timer = 3;
		bool isOnce = false;
	};
}
#endif
