#include "SplashScreen.h"

using namespace Engine;

SplashScreen::~SplashScreen() {
	delete logo;
}

void SplashScreen::Init() {
	Texture* logoTex = new Texture("Asset/Logo.png");
	logo = new Sprite(logoTex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	logo->SetPosition(550, 100, 0)->SetScale(1);
	logo->SetNumXFrames(7)->SetNumYFrames(1);
	logo->SetAnimationDuration(100);
	logo->AddAnimation("online", 0, 6)->AddAnimation("idle", 6, 6);
	logo->SetBoundingBoxSize(logo->GetScaleWidth() - (16 * logo->GetScale()),
		logo->GetScaleHeight() - (3 * logo->GetScale()));
	logo->PlayAnim("online");

	game->SetBackgroundColor(0, 0, 0);
}

void SplashScreen::Update() {
	timer += game->GetGameTime();
	if (timer > 700 && !isOnce) {
		logo->PlayAnim("idle");
		isOnce = true;
	}

	if (timer > 3000) {
		ScreenManager::GetInstance(game)->RestartScene("MainMenu");
		ScreenManager::GetInstance(game)->SetCurrentScreen("MainMenu");
	}
	logo->Update(game->GetGameTime());
}

void SplashScreen::Draw() {
	logo->Draw();
}