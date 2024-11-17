#pragma once
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "SDL.h"

class Font
{
public:
	Font(class Game* game, class SDL_Renderer* renderer);
	~Font();

	// Load/unload from a file
	bool Load(const std::string& fileName);
	void Unload();

	// Given string and this font, draw to a texture
	class SDL_Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// Map of point sizes to font data
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
	class SDL_Renderer* mRenderer;
};
