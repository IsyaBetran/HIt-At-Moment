#include "GameManager.h"

Engine::GameManager::GameManager(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Hit At Moment";
}

Engine::GameManager::~GameManager()
{
}

void Engine::GameManager::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("MainMenu", new MainMenu(setting))
		->AddScreen("Music1", new FirstMusic(setting))->AddScreen("EndScore", new EndScoreDisplay(setting))
		->AddScreen("Paused", new Pause(setting))
		->AddScreen("SplashScreen", new SplashScreen())->SetCurrentScreen("SplashScreen");

}

void Engine::GameManager::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::GameManager::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}
