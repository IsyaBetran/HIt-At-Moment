#include "EndScoreDisplay.h"

using namespace Engine;

EndScoreDisplay::~EndScoreDisplay() {
	delete bg;
	delete enterButton;
	delete characterSprite;
	delete tierText;
	delete scoreText;
	delete scoreNumber;
}

void EndScoreDisplay::Init() {
	Texture* bgTex = new Texture("Asset/End_score_bg.png");
	bg = new Sprite(bgTex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	bg->SetPosition(0, 0, -0.1f)->SetScale(10);
	bg->SetNumXFrames(1)->SetNumYFrames(1);
	bg->SetAnimationDuration(70);
	bg->AddAnimation("idle", 0, 0);
	bg->SetBoundingBoxSize(bg->GetScaleWidth() - (16 * bg->GetScale()),
		bg->GetScaleHeight() - (3 * bg->GetScale()));
	bg->PlayAnim("idle");

	Texture* enterTex = new Texture("Asset/EnterButton.png");
	enterButton = new Sprite(enterTex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	enterButton->SetPosition(1400, 150, 0.1f)->SetScale(1.5f);
	enterButton->SetNumXFrames(1)->SetNumYFrames(1);
	enterButton->SetAnimationDuration(70);
	enterButton->AddAnimation("idle", 0, 0);
	enterButton->SetBoundingBoxSize(enterButton->GetScaleWidth() - (16 * enterButton->GetScale()),
		enterButton->GetScaleHeight() - (3 * enterButton->GetScale()));
	enterButton->PlayAnim("idle");

	Texture* sprite = new Texture("Asset/Samurai_Spritelist.png");
	characterSprite = new Sprite(sprite, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	characterSprite->SetPosition(0, 0, -0.2f)->SetScale(10);
	characterSprite->SetNumXFrames(12)->SetNumYFrames(10);
	characterSprite->SetAnimationDuration(100);
	characterSprite->AddAnimation("idle", 0, 5);
	characterSprite->SetBoundingBoxSize(characterSprite->GetScaleWidth() - (16 * characterSprite->GetScale()),
		characterSprite->GetScaleHeight() - (3 * characterSprite->GetScale()));
	characterSprite->PlayAnim("idle");

	int getScore = dataManager.getScore();
	string tier = "D";
	if (getScore > 65000) {
		tier = "S";
	}
	else if (getScore > 55000) {
		tier = "A";
	}
	else if (getScore > 45000) {
		tier = "B";
	}
	else if (getScore > 35000) {
		tier = "C";
	}

	tierText = (new Text("8-bit Arcade In.ttf", 500, game->GetDefaultTextShader()))
		->SetText(tier)->SetPosition(900, 500)->SetColor(0,0,0);

	scoreText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Score")->SetPosition(1300, 600)->SetColor(0, 0, 0);

	string score = std::to_string(getScore);

	scoreNumber = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText(score)->SetPosition(1300, 500)->SetColor(0, 0, 0);

	inputManager = game->GetInputManager();
	timerOn = false;
	timer = 1000;
	game->SetBackgroundColor(188, 216, 201);
}

void EndScoreDisplay::Update() {
	bg->Update(game->GetGameTime());
	characterSprite->Update(game->GetGameTime());
	
	if (inputManager->IsKeyPressedOnce("press")) {
		timerOn = true;
	}

	if (timerOn) {
		timer -= game->GetGameTime();
	}

	if (timer < 0) {
		ScreenManager::GetInstance(game)->RestartScene("MainMenu");
		ScreenManager::GetInstance(game)->SetCurrentScreen("MainMenu");
	}
}

void EndScoreDisplay::Draw() {
	characterSprite->Draw();
	bg->Draw();
	tierText->Draw();
	scoreNumber->Draw();
	scoreText->Draw();
	enterButton->Draw();
}
