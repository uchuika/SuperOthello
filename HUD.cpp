#include "HUD.h"
#include "Game.h"
#include <string>

HUD::HUD(Game* game)
	:UIScreen(game)
	,mGame(game)
{
	mFont = mGame->GetFont("Assets/k8x12.ttf");
}
HUD::~HUD()
{

}

void HUD::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);

	UpdateStatusText(deltaTime);
}

void HUD::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* t = mFont->RenderText(mStatusText, Color::White , 72);
	DrawTexture(renderer, t, Vector2::Zero, 2.0f);
}

void HUD::SetStatusText(const std::string& text)
{
	mStatusText = text;
	//AddText(mStatusText, Vector2(500, 500));
}

void HUD::UpdateStatusText(float deltaTime) {

}