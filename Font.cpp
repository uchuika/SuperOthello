#include "Font.h"
#include <vector>
#include "Game.h"
#include "SDL.h"

Font::Font(class Game* game, class SDL_Renderer* renderer)
	:mGame(game)
	,mRenderer(renderer)
{

}

Font::~Font()
{

}

//必要なポイントサイズの配列を作成し、
//それぞれのポイントサイズのTTF_FontをmFontDataに追加する
bool Font::Load(const std::string& fileName)
{
	//サポートするフォントのサイズ
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
		//.ttfファイルをロードし、指定したポイントサイズのTTF_Fontデータのポインタを返す
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

		if (font == nullptr)
		{
			SDL_Log("フォント &s サイズ %d のロードに失敗しました",
				fileName.c_str(), size);
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

//全てのデータを開放する
void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

//文字列を受け取り適切なサイズのフォントを使ってテクスチャを生成する
SDL_Texture* Font::RenderText(
	const std::string& text,
	const Vector3& color,
	int pointSize)
{
	SDL_Texture* tex = nullptr;

	//色をSDL_Colorに変換する
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
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
}
