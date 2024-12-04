#include "MainMenu.h"

using namespace Engine;

MainMenu::~MainMenu() {
	delete bg;
	delete gameIcon;
	delete enterExit;
	delete scoremanager;
	delete score1;
	delete score2;
	delete score3;
	delete score4;
	delete score5;
}

void MainMenu::Init() {
	Texture* bgTex = new Texture("Asset/main_menu.png");
	bg = new Sprite(bgTex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	bg->SetPosition(160, 100, -0.1f)->SetScale(8.3f);
	bg->SetNumXFrames(1)->SetNumYFrames(1);
	bg->SetAnimationDuration(0);
	bg->AddAnimation("idle", 0, 0);
	bg->SetBoundingBoxSize(bg->GetScaleWidth() - (16 * bg->GetScale()),
		bg->GetScaleHeight() - (3 * bg->GetScale()));
	bg->PlayAnim("idle");

	Texture* icon1 = new Texture("Asset/firstMusiclogo.png");
	Sprite* gameIcon1 = new Sprite(icon1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameIcon1->SetPosition(300, 400, -0.2f)->SetScale(4);
	gameIcon1->SetNumXFrames(1)->SetNumYFrames(1);
	gameIcon1->SetAnimationDuration(0);
	gameIcon1->AddAnimation("idle", 0, 0);
	gameIcon1->SetBoundingBoxSize(gameIcon1->GetScaleWidth() - (16 * gameIcon1->GetScale()),
		gameIcon1->GetScaleHeight() - (3 * gameIcon1->GetScale()));
	gameIcon1->PlayAnim("idle");

	Texture* icon2 = new Texture("Asset/upcomingLogo.png");
	Sprite* gameIcon2 = new Sprite(icon2, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameIcon2->SetPosition(600, 400, -0.2f)->SetScale(4);
	gameIcon2->SetNumXFrames(1)->SetNumYFrames(1);
	gameIcon2->SetAnimationDuration(0);
	gameIcon2->AddAnimation("idle", 0, 0);
	gameIcon2->SetBoundingBoxSize(gameIcon2->GetScaleWidth() - (16 * gameIcon2->GetScale()),
		gameIcon2->GetScaleHeight() - (3 * gameIcon2->GetScale()));
	gameIcon2->PlayAnim("idle");

	gameIcon[0] = gameIcon1;
	gameIcon[1] = gameIcon2;

	Texture* enterExitTex = new Texture("Asset/enter and exit.png");
	enterExit = new Sprite(enterExitTex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	enterExit->SetPosition(200, 100, 0)->SetScale(4);
	enterExit->SetNumXFrames(1)->SetNumYFrames(1);
	enterExit->SetAnimationDuration(0);
	enterExit->AddAnimation("idle", 0, 0);
	enterExit->SetBoundingBoxSize(enterExit->GetScaleWidth() - (16 * enterExit->GetScale()),
		enterExit->GetScaleHeight() - (3 * enterExit->GetScale()));
	enterExit->PlayAnim("idle");

	//HighScore
	int scoreFromGame = dataManager.getScore();
	bool highScoreIncluded = false;
	for (int i = 0; i < highScorer.size(); i++)
	{
		if (highScorer[i] < scoreFromGame && !highScoreIncluded) {
			scoremanager->updateHighScores(scoreFromGame);
			highScoreIncluded = true;
		}
	}
	scoremanager->LoadAgain();
	highScorer.clear();
	highScorer = scoremanager->getHighScores();
	dataManager.reset();

	score1 = (new Text("prstart.ttf", 40, game->GetDefaultTextShader()))
		->SetText("1. " + std::to_string(highScorer[0]))->SetPosition(1100, 600)->SetColor(0, 0, 0);
	score2 = (new Text("prstart.ttf", 40, game->GetDefaultTextShader()))
		->SetText("2. " + std::to_string(highScorer[1]))->SetPosition(1100, 550)->SetColor(0, 0, 0);
	score3 = (new Text("prstart.ttf", 40, game->GetDefaultTextShader()))
		->SetText("3. " + std::to_string(highScorer[2]))->SetPosition(1100, 500)->SetColor(0, 0, 0);
	score4 = (new Text("prstart.ttf", 40, game->GetDefaultTextShader()))
		->SetText("4. " + std::to_string(highScorer[3]))->SetPosition(1100, 450)->SetColor(0, 0, 0);
	score5 = (new Text("prstart.ttf", 40, game->GetDefaultTextShader()))
		->SetText("5. " + std::to_string(highScorer[4]))->SetPosition(1100, 400)->SetColor(0, 0, 0);

	game->GetInputManager()->AddInputMapping("next", SDLK_RIGHT)
		->AddInputMapping("prev", SDLK_LEFT)
		->AddInputMapping("press", SDLK_RETURN)
		->AddInputMapping("exit", SDLK_ESCAPE);

	game->SetBackgroundColor(188, 216, 201);
}

void MainMenu::Update() {
	if (game->GetInputManager()->IsKeyReleased("next")) {
		if (currentButtonIndex < 1) {
			isChangeIconLeft = true;
		}
	}

	if (isChangeIconLeft) {
		ChangeIconLeft(game->GetGameTime());
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		if (currentButtonIndex > 0) {
			isChangeIconRight = true;
		}
	}

	if (isChangeIconRight) {
		ChangeIconRight(game->GetGameTime());
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		if (currentButtonIndex >= 0 && currentButtonIndex < 1) {
			ScreenManager::GetInstance(game)->RestartScene(nameGame[currentButtonIndex]);
			ScreenManager::GetInstance(game)->SetCurrentScreen(nameGame[currentButtonIndex]);
		}
	}

	if (game->GetInputManager()->IsKeyReleased("exit")) {
		game->SetState(State::EXIT);
		return;
	}
}

void MainMenu::Draw() {
	for each (Sprite* obj in gameIcon)
	{
		obj->Draw();
	}
	bg->Draw();
	enterExit->Draw();
	score1->Draw();
	score2->Draw();
	score3->Draw();
	score4->Draw();
	score5->Draw();
}

void MainMenu::ChangeIconRight(float deltaTime) {

	if (currentButtonIndex > 0) {
		vec3 oldPosCurrent = gameIcon[currentButtonIndex]->GetPosition();
		vec3 oldPosNext = gameIcon[currentButtonIndex - 1]->GetPosition();

		// Pindahkan current icon ke kanan
		if (oldPosCurrent.x < 600) {
			gameIcon[currentButtonIndex]->SetPosition(oldPosCurrent.x + 2 * deltaTime, oldPosCurrent.y, oldPosCurrent.z);
		}

		// Pindahkan next icon ke tengah
		if (oldPosNext.x < 300) {
			gameIcon[currentButtonIndex - 1]->SetPosition(oldPosNext.x + 2 * deltaTime, oldPosNext.y, oldPosNext.z);
		}

		// Periksa apakah kedua sprite telah mencapai posisi target
		if (oldPosCurrent.x >= 600 && oldPosNext.x >= 300) {
			gameIcon[currentButtonIndex]->SetPosition(600, oldPosCurrent.y, oldPosCurrent.z); // Pastikan posisi tepat
			gameIcon[currentButtonIndex - 1]->SetPosition(300, oldPosNext.y, oldPosNext.z);   // Pastikan posisi tepat

			isChangeIconRight = false;
			currentButtonIndex--;
		}
	}
}

void MainMenu::ChangeIconLeft(float deltaTime) {
	// Pastikan currentButtonIndex tidak melebihi batas
	if (currentButtonIndex < 1) { // Pastikan tidak keluar dari array
		vec3 oldPosCurrent = gameIcon[currentButtonIndex]->GetPosition();
		vec3 oldPosNext = gameIcon[currentButtonIndex + 1]->GetPosition();

		// Pindahkan current icon ke kiri
		if (oldPosCurrent.x > -600) {
			gameIcon[currentButtonIndex]->SetPosition(oldPosCurrent.x - 2 * deltaTime, oldPosCurrent.y, oldPosCurrent.z);
		}

		// Pindahkan next icon ke tengah
		if (oldPosNext.x > 300) {
			gameIcon[currentButtonIndex + 1]->SetPosition(oldPosNext.x - 2 * deltaTime, oldPosNext.y, oldPosNext.z);
		}

		// Periksa apakah kedua sprite telah mencapai posisi target
		if (oldPosCurrent.x <= -600 && oldPosNext.x <= 300) {
			gameIcon[currentButtonIndex]->SetPosition(-600, oldPosCurrent.y, oldPosCurrent.z); // Pastikan posisi tepat
			gameIcon[currentButtonIndex + 1]->SetPosition(300, oldPosNext.y, oldPosNext.z);   // Pastikan posisi tepat

			isChangeIconLeft = false;
			currentButtonIndex++;
			cout << currentButtonIndex << endl;
		}
	}
}
