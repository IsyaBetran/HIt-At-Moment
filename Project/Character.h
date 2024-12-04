#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Texture.h"
#include "BoundingBox.h"
#include <vector>

namespace Engine {
	class Character
	{
	public:
		~Character();
		void Init(Shader* spriteShader, Quad* defQuad);
		void Update(float deltaTime);
		void Render();
		void Above();
		void Down();
		BoundingBox* GetCollider();
	private:
		Sprite* characterSprite = NULL;
		float velocity = 0.04;
		bool up = false;
		bool attacking = false;
		float timerAttack = 250;
	};
}
#endif

