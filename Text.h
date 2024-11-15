#pragma once
#include "Actor.h"
#include "string"
#include "Font.h"

class Text : public Actor
{
public:

	Text(class Game* game, const std::string& text);

private:
	class Game* mGame;
	class Font* mFont;
	class TextComponent* mTextc;
};
