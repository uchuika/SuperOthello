#pragma once
#include "Component.h"
#include "SDL.h"
#include "Math.h"

class TextComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	TextComponent(class Actor* owner, int drawOrder = 100);
	~TextComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

	void SetVisible(bool visible) { mVisible = visible; }
	void SetText(const std::string& text);
	bool GetVisible() const { return mVisible; }
private:

protected:

	void DrawTexture(class SDL_Renderer* renderer, class SDL_Texture* texture,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f);

	class Game* mGame;
	class Font* mFont;
	SDL_Texture* mTextTex;

	std::string mText;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mVisible;
	Vector2 mPositions;
};