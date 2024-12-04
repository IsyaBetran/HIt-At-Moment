#include "Note.h"

using namespace Engine;

Note::~Note() {
	delete noteSprite;
}

void Note::Init(Shader* spriteShader, Quad* defQuad) {

	//Create Bird Sprite
	Texture* noteTex = new Texture("Asset/shuriken.png");
	noteSprite = new Sprite(noteTex, spriteShader, defQuad);
	noteSprite->SetPosition(2100, 100, 0.4f)->SetScale(2);
	noteSprite->SetNumXFrames(2)->SetNumYFrames(1);
	noteSprite->SetAnimationDuration(100);
	noteSprite->AddAnimation("rotate", 0, 1);
	noteSprite->SetBoundingBoxSize(noteSprite->GetScaleWidth() - (16 * noteSprite->GetScale()),
	noteSprite->GetScaleHeight() - (4 * noteSprite->GetScale()));
	noteSprite->PlayAnim("rotate");
}

void Note::Update(float deltaTime) {
	if (on) {
		vec3 birdPosOld = noteSprite->GetPosition();
		float x = birdPosOld.x, y = birdPosOld.y;
		
		x -= velocity * deltaTime;

		if (x < -40) {
			y = 100;
			x = 2100;
			on = false;
			dataManager.doneCombo();
			
		}
		noteSprite->SetPosition(x, y, 0.4f);
	
		noteSprite->Update(deltaTime);
	}
}

void Note::Render() {
	if (on) {
		noteSprite->Draw();
	}
}

BoundingBox* Note::GetCollider() {
	return noteSprite->GetBoundingBox();
}

void Note::SetOn() {
	on = true;
}

bool Note::GetOn() {
	return on;
}

void Note::SetPosition(float y) {
	noteSprite->SetPosition(2100, y, 0.4f);
}

float Note::GetPosition() {
	return noteSprite->GetPosition().x;
}

void Note::GetHit() {
	on = false;
	noteSprite->SetPosition(2100, 0, 0.4f);
}