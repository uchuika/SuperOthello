#pragma once
#include "UIScreen.h"
#include <vector>
#include "SDL.h"
#include <string>

class HUD : public UIScreen
{
public:
	//ドロー順位が低いほど後方に位置する
	HUD(class Game* game);
	~HUD();

	void Update(float deltaTime) override;
	void Draw(class SDL_Renderer* renderer) override;
	void SetStatusText(const std::string& text);

protected:

	void UpdateStatusText(float deltaTime);

	//ステータステキストを格納する変数
	std::string mStatusText;

	class Font* mFont;
	class Game* mGame;
};