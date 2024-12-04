#include "FirstMusic.h"

using namespace Engine;

FirstMusic::~FirstMusic()
{
	delete karakter;
	delete notePool;
	delete pointPool;
	delete score;
	delete combo_text;
	delete timeText;
	delete goodTextAbove;
	delete goodTextBelow;
	delete greatTextAbove;
	delete greatTextBelow;
	delete combo_bg;
	delete music;
	for (Sprite* s : backgrounds) delete s;
	for (Sprite* s : middlegrounds) delete s;
	for (Sprite* s : foregrounds) delete s;
}

void FirstMusic::Init() {
	time = 0;
	currentNumber = 0;
	previousNumber = 0;
	duplicateNumber = 0;
	musicOn = false;
	musicOffPause = false;
	hitStatusTimer = 0;
	noteCount = 0;

	backgrounds.clear();
	middlegrounds.clear();
	foregrounds.clear();

	noteTime.clear();
	GetAllMusicNote();

	//Parallax
	AddToLayer(backgrounds, "Asset/MorningLayer5.png", game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	AddToLayer(middlegrounds, "Asset/MorningLayer3.png", game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	AddToLayer(foregrounds, "Asset/MorningLayer2.png", game->GetDefaultSpriteShader(), game->GetDefaultQuad());

	noteSpawned.clear();
	for (int i = 0; i < noteTime.size(); i++)
	{
		noteSpawned.push_back(false);
	}

	srand((unsigned)std::time(0));
	
	for (int i = 0; i < 10; i++)
	{
		Note* newNote = new Note();
		newNote->Init(game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		notePool[i] = newNote;
	}

	Point* newPoint = new Point();
	newPoint->Init(game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	newPoint->SetPosition(700, 300);
	pointPool[0] = newPoint;
	
	Point* newPoint2 = new Point();
	newPoint2->Init(game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	newPoint2->SetPosition(700, 500);
	pointPool[1] = newPoint2;

	karakter = new Character();
	karakter->Init(game->GetDefaultSpriteShader(), game->GetDefaultQuad());

	//Create Input Manager
	inputManager = game->GetInputManager();
	inputManager->AddInputMapping("hitUp", SDLK_f)->AddInputMapping("hitDown", SDLK_j)->AddInputMapping("Quit", SDLK_ESCAPE);

	Texture* sprite = new Texture("Asset/bg_combo.png");
	combo_bg = new Sprite(sprite, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	combo_bg->SetPosition(460, 675, -0.1f)->SetScale(5);
	combo_bg->SetNumXFrames(1)->SetNumYFrames(1);
	combo_bg->SetAnimationDuration(70);
	combo_bg->AddAnimation("idle", 0, 0);
	combo_bg->SetBoundingBoxSize(combo_bg->GetScaleWidth() - (16 * combo_bg->GetScale()),
		combo_bg->GetScaleHeight() - (4 * combo_bg->GetScale()));
	combo_bg->PlayAnim("idle");

	combo_text = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Combo")->SetPosition(500, 850)->SetColor(24, 64, 82);

	score = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("0")->SetPosition(500, 800)->SetColor(24, 64, 82);

	goodTextAbove = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Good")->SetPosition(750, 550)->SetColor(255, 255, 255)->SetScale(0.4);

	goodTextBelow = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Good")->SetPosition(750, 350)->SetColor(255, 255, 255)->SetScale(0.4);

	greatTextAbove = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Great")->SetPosition(750, 550)->SetColor(255, 255, 255)->SetScale(0.4);

	greatTextBelow = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Great")->SetPosition(750, 350)->SetColor(255, 255, 255)->SetScale(0.4);

	music = (new Music("Asset/A_Bit_Of_Hope_-_David_Fesliyan.ogg"))->SetVolume(40)->Play(false)->Pause();

	game->SetBackgroundColor(188, 216, 201);
}

void FirstMusic::Update() {
	if (musicOffPause) {
		music->Resume();
		musicOffPause = false;
	}
	time += game->GetGameTime();

	MoveLayer(backgrounds, speed * 0.1f, game->GetGameTime(), -0.4);
	MoveLayer(middlegrounds, speed * 0.3f, game->GetGameTime(), -0.3);
	MoveLayer(foregrounds, speed * 0.5f, game->GetGameTime(), -0.2);

	if (time > 3500 && !musicOn) {
		music->Resume();
		musicOn = true;
	}

	if (time > 207000) {
		ScreenManager::GetInstance(game)->RestartScene("EndScore");
		ScreenManager::GetInstance(game)->SetCurrentScreen("EndScore");
	}
	
	for (Point* i : pointPool) {
		i->Update(game->GetGameTime());
	}

	for (Note* i : notePool) {
		i->Update(game->GetGameTime());
	}
	karakter->Update(game->GetGameTime());

	if (inputManager->IsKeyPressedOnce("hitUp")) {
		karakter->Above();
		CheckAbove();
	}

	if (inputManager->IsKeyPressedOnce("hitDown")) {
		karakter->Down();
		CheckBelow();
	}

	if (inputManager->IsKeyReleased("exit")) {
		ScreenManager::GetInstance(game)->RestartScene("Paused");
		music->Pause();
		musicOffPause = true;
		ScreenManager::GetInstance(game)->SetCurrentScreen("Paused");
	}

	if (noteCount < noteTime.size() - 1 && time >= noteTime[noteCount]) {
		if (!noteSpawned[noteCount]) {
			CheckNotePool();
			noteSpawned[noteCount] = true;
			noteCount++;
		}
	}

	score->SetText(to_string(dataManager.getComboPoint()));

	//Ini untuk timer mengeluarkan text good dan great
	if (hitStatusTimer > 0) {
		hitStatusTimer -= game->GetGameTime() / 1000;
	}
	else {
		DisableAllStatusText();
	}
}

void FirstMusic::Draw() {

	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);

	//tampilkan good atau great
	if (hitStatusTimer > 0 && isGoodAbove) {
		goodTextAbove->Draw();
	}
	else if (hitStatusTimer > 0 && isGoodBelow) {
		goodTextBelow->Draw();
	}
	else if (hitStatusTimer > 0 && isGreatAbove) {
		greatTextAbove->Draw();
	}
	else if (hitStatusTimer > 0 && isGreatBelow) {
		greatTextBelow->Draw();
	}
	if (dataManager.getComboPoint() > 1) {
		combo_bg->Draw();
		combo_text->Draw();
		score->Draw();
	}

	//Yang lainnya
	for (Point* i : pointPool) {
		i->Render();
	}
	karakter->Render();
	for (Note* i : notePool) {
		i->Render();
	}
}

void FirstMusic::CheckNotePool() {
	for (Note* i : notePool) {
		bool NoteOn = i->GetOn();
		if (!NoteOn) {

			//Fungsi Random
			currentNumber = (rand() % 2 == 0) ? 275 : 475;
			if (currentNumber == previousNumber) {
				++duplicateNumber;
			}
			else {
				duplicateNumber = 1;
			}

			if (duplicateNumber > 4) {
				currentNumber = (currentNumber == 275) ? 475 : 275;
				duplicateNumber = 1; 
			}

			previousNumber = currentNumber;

			i->SetPosition(currentNumber);
			i->SetOn();
			return;
		}
	}
}

void FirstMusic::CheckAbove() {
	for (Note* i : notePool) {
		if (i->GetOn()) {
			if (pointPool[1]->GetCollider()->CollideWith(i->GetCollider())) {
				if (abs(700 - i->GetPosition()) > 20) {
					DisableAllStatusText();
					hitStatusTimer = 0.5f;
					isGoodAbove = true;
					dataManager.setScore(100);
				}
				else {
					DisableAllStatusText();
					hitStatusTimer = 0.5f;
					isGreatAbove = true;
					dataManager.setScore(200);
				}
				i->GetHit();
				dataManager.setCombo();
			}
		}
	}
}

void FirstMusic::CheckBelow() {
	for (Note* i : notePool) {
		if (i->GetOn()) {
			if (pointPool[0]->GetCollider()->CollideWith(i->GetCollider())) {
				if (abs(700 - i->GetPosition()) > 20) {
					DisableAllStatusText();
					hitStatusTimer = 0.5f;
					isGoodBelow = true;
					dataManager.setScore(100);
				}
				else {
					DisableAllStatusText();
					hitStatusTimer = 0.5f;
					isGreatBelow = true;
					dataManager.setScore(200);
				}
				i->GetHit();
				dataManager.setCombo();
			}
		}
	}
}

void FirstMusic::DisableAllStatusText() {
	isGoodAbove = false;
	isGreatAbove = false;
	isGoodBelow = false;
	isGreatBelow = false;
}

void FirstMusic::GetAllMusicNote() {
	MusicNoteReader fileReader("FirstMusicPointTime.txt");

	noteTime = fileReader.readNumbers();
}

void FirstMusic::MoveLayer(std::vector<Sprite*>& bg, float speed, float deltaTime, float z)
{
	// Cari sprite paling belakang untuk menghitung posisi terjauh di layer
	float maxX = bg[0]->GetPosition().x;
	for (Sprite* s : bg) {
		if (s->GetPosition().x > maxX) {
			maxX = s->GetPosition().x;
		}
	}

	for (Sprite* s : bg) {
		float x = s->GetPosition().x;
		if (x < -setting->screenWidth + offset) {
			// Pindahkan ke belakang sprite paling belakang
			x = maxX + 1920;
		}
		s->SetPosition(x - speed * deltaTime, s->GetPosition().y, z);
		s->Update(deltaTime);
	}
}


void FirstMusic::DrawLayer(std::vector<Sprite*>& bg)
{
	for (Sprite* s : bg) {
		s->Draw();
	}
}

void FirstMusic::AddToLayer(std::vector<Sprite*>& bg, std::string name, Shader* defaultSpriteShader, Quad* defaultQuad)
{
	Texture* texture = new Texture(name);

	Sprite* s = new Sprite(texture, defaultSpriteShader, defaultQuad);
	s->SetSize(setting->screenWidth, setting->screenHeight);
	bg.push_back(s);

	Sprite* s2 = new Sprite(texture, defaultSpriteShader, defaultQuad);
	s2->SetSize(setting->screenWidth, setting->screenHeight)->SetPosition(setting->screenWidth, 0);
	bg.push_back(s2);

	Sprite* s3 = new Sprite(texture, defaultSpriteShader, defaultQuad);
	s3->SetSize(setting->screenWidth, setting->screenHeight)->SetPosition(setting->screenWidth * 2, 0);
	bg.push_back(s3);
}