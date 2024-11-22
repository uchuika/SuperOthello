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
	SDL_Texture* t = mFont->RenderText(mStatusText, mStatusColor , 72);
	DrawTexture(renderer, t, Vector2::Zero, 2.0f);

	if (isEndGame) {
		SDL_Texture* resultT;
		std::vector<std::string> resultMessage { u8"çï" + mBlack, u8"îí" + mWhite };
		for (int i = 0; i < 2; i++) {
			resultT = mFont->RenderText(resultMessage[i]);
			DrawTexture(renderer, resultT, Vector2{ 50, static_cast<float>(50+72*i)}, 2.0f);
		}
	}
}

void HUD::SetResultText(const int black, const int white)
{
	mBlack = black;
	mWhite = white;
}

void HUD::SetStatusText(const std::string& text, const Vector3& color)
{
	mStatusText = text;
	mStatusColor = color;
	//AddText(mStatusText, Vector2(500, 500));
}


void HUD::SetEndGame(const bool endgame)
{
	isEndGame = endgame;
}

void HUD::UpdateStatusText(float deltaTime) {

}