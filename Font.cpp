// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Font.h"
#include "SDL.h"
#include <vector>
#include "Game.h"
#include "SDL_ttf.h"

Font::Font(class Game* game, class SDL_Renderer* renderer)
	:mGame(game)
	,mRenderer(renderer)
{

}

Font::~Font()
{

}

bool Font::Load(const std::string& fileName)
{
	// We support these font sizes
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

SDL_Texture* Font::RenderText(const std::string& textKey,
	const Vector3& color /*= Color::White*/,
	int pointSize /*= 24*/)
{
	SDL_Texture* texture = nullptr;

	// Convert to SDL_Color
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// Find the font data for this point size
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = mGame->GetText(textKey);
		// Draw this to a surface (blended for alpha)
		SDL_Surface* surf = TTF_RenderText_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// Convert from surface to texture
			texture = SDL_CreateTextureFromSurface(mRenderer, surf);
			SDL_FreeSurface(surf);
			if (!texture)
			{
				SDL_Log("サーフェスをテクスチャに変換できませんでした %s", actualText.c_str());
			}
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}
