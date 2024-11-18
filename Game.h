#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "Font.h"
#include "HUD.h"

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

<<<<<<< HEAD
	void AddText(class TextComponent* text);
	void RemoveText(class TextComponent* text);

	SDL_Texture* GetTexture(const std::string& fileName);

	class Font* GetFont(const std::string & fileName);
=======
	class HUD* GetHUD() { return mHUD; }

	SDL_Texture* GetTexture(const std::string& fileName);

	//スクリーン幅を返す
	float GetScreenWidth() const { return mScreenWidth; }

	//スクリーン高さを返す
	float GetScreenHeight() const { return mScreenHeight; }

	//テキストファイルからテキストを読み込む関数
	const std::string& GetText(const std::string& key);
	
	//フォント取得関数
	Font* GetFont(const std::string& fileName);

	//UIスタックの管理
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	//指定のUIScreenをスタックにプッシュする
	void PushUI(class UIScreen* screen);
>>>>>>> addTextRenderSystem

	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	//テキストのローカライズ用マップ
	std::unordered_map<std::string, std::string> mText;

	// 読み込まれたテクスチャのマップ
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::unordered_map<std::string, class Font*> mFonts;

	// 全てのアクターを保管する配列
	std::vector<class Actor*> mActors;
	//ゲーム用のUIスタック
	std::vector<class UIScreen*> mUIStack;
	std::unordered_map<std::string, class Font*> mFonts;

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

	class HUD* mHUD;

	Uint32 mTicksCount;
	bool mIsRunning;
	// 現在アクターを更新しているかどうか
	bool mUpdatingActors;

	//スクリーンの高さと幅
	int mScreenWidth;
	int mScreenHeight;

	// Game-specific
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;
};
