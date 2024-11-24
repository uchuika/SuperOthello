#include "HUD.h"
#include "Game.h"
#include <string>

HUD::HUD(Game* game)
	:UIScreen(game)
	,mGame(game)
	,isEndGame(false)
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

		std::string blackSt = u8"çï: ";
		std::string whiteSt = u8"îí: ";

		SDL_Texture* resultT;
		std::vector<std::string> resultMessage { blackSt.append(mBlack), whiteSt.append(mWhite)};
		for (int i = 0; i < 2; i++) {
			resultT = mFont->RenderText(resultMessage[i], Color::White, 72);
			DrawTexture(renderer, resultT, Vector2{ 700, static_cast<float>(50+150*i)}, 2.0f);
		}
	}
}

void HUD::SetResultText(const int black, const int white)
{
	std::string blackSt = std::to_string(black);
	std::string whiteSt = std::to_string(white);
	mBlack = u8"" + blackSt;
	mWhite = u8"" + whiteSt;
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