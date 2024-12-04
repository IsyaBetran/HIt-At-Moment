#include "Point.h"

using namespace Engine;

Point::~Point() {
	delete pointSprite;
}

void Point::Init(Shader* spriteShader, Quad* defQuad) {
	Texture* pointTex = new Texture("Asset/Pointnew.png");
	pointSprite = new Sprite(pointTex, spriteShader, defQuad);
	pointSprite->SetPosition(2100, 100, 0.1)->SetScale(1.5f);
	pointSprite->SetNumXFrames(2)->SetNumYFrames(1);
	pointSprite->SetAnimationDuration(250);
	pointSprite->AddAnimation("idle", 0, 1);
	pointSprite->SetBoundingBoxSize(pointSprite->GetScaleWidth() - (16 * pointSprite->GetScale()),pointSprite->GetScaleHeight() - (4 * pointSprite->GetScale()));
	pointSprite->PlayAnim("idle");
}

void Point::Update(float deltaTime) {
	pointSprite->Update(deltaTime);
}

void Point::Render() {
	pointSprite->Draw();
}

BoundingBox* Point::GetCollider() {
	return pointSprite->GetBoundingBox();
}

void Point::SetPosition(float x, float y) {
	pointSprite->SetPosition(x, y, 0.3f);
}

