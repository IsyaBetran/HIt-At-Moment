#include "Pause.h"

using namespace Engine;

Pause::~Pause() {
	delete tombol;
}

void Pause::Init() {
	currentTombol = 0;

	Texture* icon1 = new Texture("Asset/resume_sprite.png");
	Sprite* gameIcon1 = new Sprite(icon1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameIcon1->SetPosition(500, 450, 0)->SetScale(4);
	gameIcon1->SetNumXFrames(2)->SetNumYFrames(1);
	gameIcon1->SetAnimationDuration(300);
	gameIcon1->AddAnimation("notSelected", 0, 0)->AddAnimation("selected", 0 ,1);
	gameIcon1->SetBoundingBoxSize(gameIcon1->GetScaleWidth() - (16 * gameIcon1->GetScale()),
		gameIcon1->GetScaleHeight() - (3 * gameIcon1->GetScale()));
	gameIcon1->PlayAnim("selected");

	tombol[0] = gameIcon1;

	icon1 = new Texture("Asset/restart_sprite.png");
	gameIcon1 = new Sprite(icon1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameIcon1->SetPosition(800, 450, 0)->SetScale(4);
	gameIcon1->SetNumXFrames(2)->SetNumYFrames(1);
	gameIcon1->SetAnimationDuration(300);
	gameIcon1->AddAnimation("notSelected", 0, 0)->AddAnimation("selected", 0, 1);
	gameIcon1->SetBoundingBoxSize(gameIcon1->GetScaleWidth() - (16 * gameIcon1->GetScale()),
		gameIcon1->GetScaleHeight() - (3 * gameIcon1->GetScale()));
	gameIcon1->PlayAnim("notSelected");

	tombol[1] = gameIcon1;

	icon1 = new Texture("Asset/home_sprite.png");
	gameIcon1 = new Sprite(icon1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameIcon1->SetPosition(1100, 450, 0)->SetScale(4);
	gameIcon1->SetNumXFrames(2)->SetNumYFrames(1);
	gameIcon1->SetAnimationDuration(300);
	gameIcon1->AddAnimation("notSelected", 0, 0)->AddAnimation("selected", 0, 1);
	gameIcon1->SetBoundingBoxSize(gameIcon1->GetScaleWidth() - (16 * gameIcon1->GetScale()),
		gameIcon1->GetScaleHeight() - (3 * gameIcon1->GetScale()));
	gameIcon1->PlayAnim("notSelected");

	tombol[2] = gameIcon1;

	game->SetBackgroundColor(188, 216, 201);
}

void Pause::Update() {
	if (game->GetInputManager()->IsKeyReleased("next")) {
		if (currentTombol < 2) {
			tombol[currentTombol]->PlayAnim("notSelected");
			currentTombol++;
			tombol[currentTombol]->PlayAnim("selected");
		}
	}


	if (game->GetInputManager()->IsKeyReleased("prev")) {
		if (currentTombol > 0) {
			tombol[currentTombol]->PlayAnim("notSelected");
			currentTombol--;
			tombol[currentTombol]->PlayAnim("selected");
		}
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		if (currentTombol == 0) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("Music1");
		}
		else if (currentTombol == 1) {
			ScreenManager::GetInstance(game)->RestartScene("Music1");
			dataManager.reset();
			ScreenManager::GetInstance(game)->SetCurrentScreen("Music1");
		}
		else if (currentTombol == 2) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("MainMenu");
		}
	}

	for (int i = 0; i < 3; i++)
	{
		tombol[i]->Update(game->GetGameTime());
	}
}

void Pause::Draw() {
	for (int i = 0; i < 3; i++)
	{
		tombol[i]->Draw();
	}
}