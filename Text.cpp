
#include "Actor.h"
#include "TextComponent.h"
#include "Game.h"
#include "Text.h"

Text::Text(class Game* game)
	:Actor(game)
	,mText(nullptr)
	,mFont(nullptr)
{
	mText = new TextComponent(this);
	mFont = mGame->GetFont("Assets/k8x12.ttf");
}


