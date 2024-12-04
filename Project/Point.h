#ifndef POINT_H
#define POINT_H

#include "Sprite.h"
#include "Texture.h"
#include "BoundingBox.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Engine {
	class Point
	{
	public:
		~Point();
		void Init(Shader* spriteShader, Quad* defQuad);
		void Update(float deltaTime);
		void Render();
		BoundingBox* GetCollider();
		void SetPosition(float x, float y);
	private:
		Sprite* pointSprite = NULL;
		float velocity = 0.5;
		bool on = false;
	};
}
#endif

