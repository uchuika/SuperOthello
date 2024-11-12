#pragma once
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "SDL.h"

class Font
{
public:
	Font(class Game* game,class SDL_Renderer* renderer);
	~Font();

	//ファイルのロードとアンロードの関数
	bool Load(const std::string& filename);
	void Unload();

	//文字列をテクスチャに描画
	class SDL_Texture* RenderText(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 30
	);

private:
	//ポイントサイズとフォントデータの連想配列
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
	class SDL_Renderer* mRenderer;
};
