#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>
#include "SDL.h"

class Text
{
public:
	Text(const std::string& name, class Font* font,
		const Vector2& pos, const Vector2& dims);
	~Text();

	//ゲッターとセッター
	class SDL_Texture* GetTextTex() { return mTextTex; }
	const Vector2& GetPosition() const { return mPosition; }

	//表示するテキストを設定する関数
	void SetRenderText(const std::string& text);

private:
	std::string mText;
	class SDL_Texture* mTextTex;
	class Font* mFont;
	Vector2 mPosition;
	Vector2 mDimensions;

};

class Button
{
public:
	Button(const std::string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// ボタンの名前を設定する
	void SetName(const std::string& name);

	// ゲッターとセッター
	class SDL_Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	// ポインターがボタンの範囲ないにある場合trueを返す
	bool ContainsPoint(const Vector2& pt) const;
	// ボタンがクリックされたときに呼び出し
	void OnClick();
private:
	//ボタンがクリックされた時に実行される関数のポインタ
	std::function<void()> mOnClick;
	std::string mName;
	class SDL_Texture* mNameTex;
	class Font* mFont;
	Vector2 mPosition;
	Vector2 mDimensions;
	bool mHighlighted;
};

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();
	//UIScreenの派生クラスは以上をオーバーライドできる
	virtual void Update(float deltaTime);
	virtual void Draw(class SDL_Renderer* renderer);
	virtual void ProcessInput(const uint8_t* kyes);
	virtual void HandleKeyPress(int key);
	//状態をクロージングにする
	void Close();
	//状態がアクティブがクロージングかを管理
	enum UIState { 
		EActive, 
		EClosing 
	};

	//状態を取得
	UIState GetState() const { return mState; }

	// タイトルを変更する関数
	void SetTitle(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 40);
	// ボタンをスクリーンについか
	void AddButton(const std::string& name, std::function<void()>onClick);

	//テキストをスクリーンについか
	void AddText(const std::string& name, const Vector2& pos);

protected:
	//テクスチャを描画するヘルパー関数
	void DrawTexture(class SDL_Renderer* renderer, class SDL_Texture* texture,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f);

	// マウスモードを相対モードにするかどうかを設定する
	void SetRelativeMouseMode(bool relative);
	class Game* mGame;
	
	//UI画面のタイトル文字列用
	class Font* mFont;
	class SDL_Texture* mTitle;

	class SDL_Texture* mBackground;
	class SDL_Texture* mButtonOn;
	class SDL_Texture* mButtonOff;

	Vector2 mTitlePos;
	Vector2 mNextButtonPos;
	Vector2 mBGPos;
	//状態
	UIState mState;
	// ボタンのリスト
	std::vector<Button*> mButtons;

	//テキストのリスト
	std::vector<Text*> mTexts;
};
