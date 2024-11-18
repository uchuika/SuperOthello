<<<<<<< HEAD
#include "Font.h"
#include <vector>
#include "Game.h"
#include "SDL.h"
=======
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
>>>>>>> addTextRenderSystem

Font::Font(class Game* game, class SDL_Renderer* renderer)
	:mGame(game)
	,mRenderer(renderer)
{

}

Font::~Font()
{

}

<<<<<<< HEAD
//必要なポイントサイズの配列を作成し、
//それぞれのポイントサイズのTTF_FontをmFontDataに追加する
bool Font::Load(const std::string& fileName)
{
	//サポートするフォントのサイズ
=======
bool Font::Load(const std::string& fileName)
{
	// We support these font sizes
>>>>>>> addTextRenderSystem
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
<<<<<<< HEAD
		//.ttfファイルをロードし、指定したポイントサイズのTTF_Fontデータのポインタを返す
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

		if (font == nullptr)
		{
			SDL_Log("フォント &s サイズ %d のロードに失敗しました",
				fileName.c_str(), size);
=======
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
>>>>>>> addTextRenderSystem
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

<<<<<<< HEAD
//全てのデータを開放する
=======
>>>>>>> addTextRenderSystem
void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

<<<<<<< HEAD
//文字列を受け取り適切なサイズのフォントを使ってテクスチャを生成する
SDL_Texture* Font::RenderText(
	const std::string& text,
	const Vector3& color,
	int pointSize)
{
	SDL_Texture* tex = nullptr;

	//色をSDL_Colorに変換する
=======
SDL_Texture* Font::RenderText(const std::string& textKey,
	const Vector3& color /*= Color::White*/,
	int pointSize /*= 24*/)
{
	SDL_Texture* texture = nullptr;

	// Convert to SDL_Color
>>>>>>> addTextRenderSystem
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
<<<<<<< HEAD
	sdlColor.b = 255;

	//指定サイズのフォントデータを探す
	auto iter = mFontData.find(pointSize);

	/*
	for (auto mfont : mFontData) {
		if (mfontnullptr) {

		}
	}
	*/

	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		//SDL_Surfaceに描画(アルファブレンディング)
		SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(),
			sdlColor);

		if (surf != nullptr)
		{
			//SDL_Surfaceからテクスチャに変換
			tex = SDL_CreateTextureFromSurface(mRenderer, surf);
			SDL_FreeSurface(surf);
			if (!tex)
			{
				SDL_Log("サーフェスをテクスチャに変換できませんでした %s", text.c_str());
				return nullptr;
			}
		}
	}
	else 
	{
		SDL_Log("ポイントサイズ %d が未対応です", pointSize);
	}
	return tex;
=======
	sdlColor.a = 255;

	// Find the font data for this point size
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		//const std::string& actualText = mGame->GetText(textKey);
		const std::string& actualText = textKey;
		// Draw this to a surface (blended for alpha)
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
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
>>>>>>> addTextRenderSystem
}
