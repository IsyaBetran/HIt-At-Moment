#ifndef FIRSTMUSIC_H
#define FIRSTMUSIC_H

#include "Screen.h"
#include "Setting.h"
#include "Character.h"
#include "Note.h"
#include "Point.h"
#include "GameData.h"
#include "Text.h"
#include "MusicNoteReader.h"
#include "Music.h"
#include "Texture.h"
#include "Sprite.h"
#include "ScreenManager.h"
#include <vector>
#include <cmath>

namespace Engine {
	class FirstMusic :
		public Engine::Screen
	{
	public:
		FirstMusic(Setting* set) : dataManager(GameData::getInstance()) { setting = set;}
		~FirstMusic();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		//Keperluan external
		GameData& dataManager;
		Character* karakter = NULL;
		Note* notePool[10];
		Point* pointPool[2];
		Setting* setting;

		//Method
		void CheckNotePool();
		void CheckAbove();
		void CheckBelow();
		void DisableAllStatusText();
		void GetAllMusicNote();
		void MoveLayer(std::vector<Sprite*>& bg, float speed, float deltaTime, float z);
		void DrawLayer(std::vector<Sprite*>& bg);
		void AddToLayer(std::vector<Sprite*>& bg, std::string name, Shader* defaultSpriteShader, Quad* defaultQuad);

		//Variabel
		Input* inputManager;
		Text* score;
		Text* combo_text;
		Text* timeText;
		Text* goodTextAbove;
		Text* goodTextBelow;
		Text* greatTextAbove;
		Text* greatTextBelow;

		Sprite* combo_bg;

		float time = 0;
		float hitStatusTimer = 0;
		int noteCount = 0;

		float currentNumber = 0;
		float previousNumber = 0;
		int duplicateNumber = 0;
		std::vector<float> noteTime;
		std::vector<bool> noteSpawned;
		bool isGoodAbove;
		bool isGoodBelow;
		bool isGreatAbove;
		bool isGreatBelow;

		//Audio
		Music* music = NULL;
		bool musicOn = false;
		bool musicOffPause = false;

		// Parallax 
		std::vector<Sprite*> backgrounds, middlegrounds, foregrounds;
		float offset = 0;
		float speed = 0.5;
	};
}
#endif

