#include "Character.h"

using namespace Engine;

Character::~Character() {
	delete characterSprite;
}

void Character::Init(Shader* spriteShader, Quad* defaultQuad) {
	//Create Character Sprite
	Texture* sprite = new Texture("Asset/Samurai_Spritelist.png");
	characterSprite = new Sprite(sprite, spriteShader, defaultQuad);
	characterSprite->SetPosition(300, 200, 0.3f)->SetScale(4);
	characterSprite->SetNumXFrames(12)->SetNumYFrames(10);
	characterSprite->SetAnimationDuration(70);
	characterSprite->AddAnimation("run", 24, 31)->AddAnimation("jump", 45, 45)->AddAnimation("attack", 51, 53);
	characterSprite->SetBoundingBoxSize(characterSprite->GetScaleWidth() - (16 * characterSprite->GetScale()),
	characterSprite->GetScaleHeight() - (3 * characterSprite->GetScale()));
	characterSprite->PlayAnim("run");

	
}

void Character::Update(float deltaTime) {

	vec3 oldCharPos = characterSprite->GetPosition();
	float x = oldCharPos.x ,y = oldCharPos.y;

	if (attacking) {
		timerAttack -= deltaTime;
		if (timerAttack < 0) {
			if (up) {
				characterSprite->PlayAnim("jump");
			}
			else {
				characterSprite->PlayAnim("run");
			}
			timerAttack = 250;
			attacking = false;
		}
	}
	else {
		if (up && y > 200) {
			y -= 0.5f * deltaTime;
			characterSprite->SetPosition(x, y, 0.3f);
		}
		else {
			up = false;
			characterSprite->PlayAnim("run");
		}
	}

	//update animasi
	characterSprite->Update(deltaTime);
}

void Character::Render() {
	characterSprite->Draw();
}

BoundingBox* Character::GetCollider() {
	return characterSprite->GetBoundingBox();
}

void Character::Above() {
	vec3 oldCharPos = characterSprite->GetPosition();
	float x = oldCharPos.x, y = oldCharPos.y;

	if (up) {
		characterSprite->SetPosition(x, 400, 0.3f);
		characterSprite->PlayAnim("attack");
	}
	else {
		characterSprite->SetPosition(x, 400, 0.3f);
		characterSprite->PlayAnim("attack");
		up = true;
	}
	attacking = true;
}

void Character::Down() {
	vec3 oldCharPos = characterSprite->GetPosition();
	float x = oldCharPos.x, y = oldCharPos.y;

	if (up) {
		characterSprite->SetPosition(x, 200, 0.3f);
		characterSprite->PlayAnim("attack");
		up = false;
	}
	else {
		characterSprite->PlayAnim("attack");
	}
	attacking = true;
}