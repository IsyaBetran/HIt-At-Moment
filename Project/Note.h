#ifndef NOTE_H
#define NOTE_H

#include "Sprite.h"
#include "Texture.h"
#include "BoundingBox.h"
#include "GameData.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Engine {
	class Note
	{
	public:
		Note() : dataManager(GameData::getInstance()) {}
		~Note();
		void Init(Shader* spriteShader, Quad* defQuad);
		void Update(float deltaTime);
		void Render();
		void SetOn();
		bool GetOn();
		void SetPosition(float y);
		float GetPosition();
		void GetHit();
		BoundingBox* GetCollider();
	private:
		GameData& dataManager;
		Sprite* noteSprite = NULL;
		float velocity = 0.5;
		bool on = false;
		//waktu pas untuk hit 3000ms 
	};
}
#endif

