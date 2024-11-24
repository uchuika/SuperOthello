#pragma once
#include "UIScreen.h"
#include <vector>
#include "SDL.h"
#include <string>
#include <math.h>

class HUD : public UIScreen
{
public:
	//ドロー順位が低いほど後方に位置する
	HUD(class Game* game);
	~HUD();

	void Update(float deltaTime) override;
	void Draw(class SDL_Renderer* renderer) override;
	void SetStatusText(const std::string& text, const Vector3& color = Color::White);
	void SetResultText(const int blackCount, const int whiteCount);
	void SetEndGame(const bool endgameBool);

protected:

	void UpdateStatusText(float deltaTime);

	//ステータステキストを格納する変数
	std::string mStatusText;

	class Font* mFont;
	class Game* mGame;

	bool isEndGame;

	std::string mBlack = u8"";
	std::string mWhite = u8"";

	Vector3 mStatusColor;
};