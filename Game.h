#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddText(class TextComponent* text);
	void RemoveText(class TextComponent* text);

	SDL_Texture* GetTexture(const std::string& fileName);

	class Font* GetFont(const std::string & fileName);

	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// 読み込まれたテクスチャのマップ
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::unordered_map<std::string, class Font*> mFonts;

	// 全てのアクターを保管する配列
	std::vector<class Actor*> mActors;
	// 待機中のアクターを保管する配列
	std::vector<class Actor*> mPendingActors;

	//全ての描画用テキストを保管する配列
	std::vector<class TextComponent*> mTexts;

	//全ての待機中の描画用テキストを保管する配列
	//std::vector<

	// 描画された全てのスプライトコンポーネントの配列
	std::vector<class SpriteComponent*> mSprites;

	//各種動作用メンバ変数
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// 現在アクターを更新しているかどうか
	bool mUpdatingActors;

	// Game-specific
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;
};
