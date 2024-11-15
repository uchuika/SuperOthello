
#include "Actor.h"
#include "TextComponent.h"
#include "Game.h"
#include "Text.h"


Text::Text(class Game* game, const std::string& text)
	:Actor(game)
	,mTextc(nullptr)
	,mFont(nullptr)
{
	mGame = game;
	mTextc = new TextComponent(this);
	mFont = mGame->GetFont("Assets/k8x12.ttf");

	mTextc->SetText(text);
}


