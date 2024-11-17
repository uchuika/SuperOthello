#include "UIScreen.h"
#include "SDL.h"
//#include "Shader.h"
#include "Game.h"
//#include "Renderer.h"
#include "Font.h"

UIScreen::UIScreen(Game* game)
	:mGame(game)
	, mTitle(nullptr)
	, mBackground(nullptr)
	, mTitlePos(0.0f, 300.0f)
	, mNextButtonPos(0.0f, 200.0f)
	, mBGPos(0.0f, 250.0f)
	, mState(EActive)
{
	// Add to UI Stack
	mGame->PushUI(this);
	mFont = mGame->GetFont("Assets/k8x12.ttf");
	mButtonOn = mGame->GetTexture("Assets/ButtonYellow.png");
	mButtonOff = mGame->GetTexture("Assets/ButtonBlue.png");
}

UIScreen::~UIScreen()
{
	if (mTitle)
	{
		SDL_DestroyTexture(mTitle);
		delete mTitle;
	}

	for (auto b : mButtons)
	{
		delete b;
	}
	mButtons.clear();
}

void UIScreen::Update(float deltaTime)
{

}

void UIScreen::Draw(SDL_Renderer* renderer)
{
	// Draw background (if exists)
	if (mBackground)
	{
		DrawTexture(renderer, mBackground, mBGPos);
	}
	// Draw title (if exists)
	if (mTitle)
	{
		DrawTexture(renderer, mTitle, mTitlePos);
	}
	// Draw buttons
	for (auto b : mButtons)
	{
		// Draw background of button
		SDL_Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
		DrawTexture(renderer, tex, b->GetPosition());
		// Draw text of button
		DrawTexture(renderer, b->GetNameTex(), b->GetPosition());
	}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t* keys)
{
	// Do we have buttons?
	if (!mButtons.empty())
	{
		// Get position of mouse
		int x, y;
		SDL_GetMouseState(&x, &y);
		// Convert to (0,0) center coordinates
		Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
		mousePos.x -= mGame->GetScreenWidth() * 0.5f;
		mousePos.y = mGame->GetScreenHeight() * 0.5f - mousePos.y;

		// Highlight any buttons
		for (auto b : mButtons)
		{
			if (b->ContainsPoint(mousePos))
			{
				b->SetHighlighted(true);
			}
			else
			{
				b->SetHighlighted(false);
			}
		}
	}
}

void UIScreen::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
		if (!mButtons.empty())
		{
			for (auto b : mButtons)
			{
				if (b->GetHighlighted())
				{
					b->OnClick();
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::SetTitle(const std::string& text,
	const Vector3& color,
	int pointSize)
{
	// Clear out previous title texture if it exists
	if (mTitle)
	{
		SDL_DestroyTexture(mTitle);
		delete mTitle;
		mTitle = nullptr;
	}
	mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	int buttonOnWidth;
	int buttonOnHeight;
	SDL_QueryTexture(mButtonOn, nullptr, nullptr, &buttonOnWidth, &buttonOnHeight);
	Vector2 dims(static_cast<float>(buttonOnWidth),
		static_cast<float>(buttonOnHeight));
	Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
	mButtons.emplace_back(b);

	// 次のボタンの位置を更新
	// ボタンの高さ＋パディングで下に移動
	int buttonOffWidth;
	int buttonOffHeight;
	SDL_QueryTexture(mButtonOff, nullptr, nullptr, &buttonOffWidth, &buttonOffHeight);
	mNextButtonPos.y -= buttonOffHeight + 20.0f;
}

void UIScreen::DrawTexture(class SDL_Renderer* renderer, class SDL_Texture* texture,
	const Vector2& offset, float scale)
{
	SDL_Rect r;
	// Scale the width/height by owner's scale
	int texWidth;
	int texHeight;
	SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
	r.w = static_cast<int>(texWidth);
	r.h = static_cast<int>(texHeight);
	// Center the rectangle around the position of the owner
	r.x = static_cast<int>(offset.x);
	r.y = static_cast<int>(offset.y);

	// Draw (have to convert angle from radians to degrees, and clockwise to counter)
	SDL_RenderCopyEx(renderer,
		texture,
		nullptr,
		&r,
		0,
		nullptr,
		SDL_FLIP_NONE);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
	if (relative)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		// Make an initial call to get relative to clear out
		SDL_GetRelativeMouseState(nullptr, nullptr);
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}

Button::Button(const std::string& name, Font* font,
	std::function<void()> onClick,
	const Vector2& pos, const Vector2& dims)
	:mOnClick(onClick)
	, mNameTex(nullptr)
	, mFont(font)
	, mPosition(pos)
	, mDimensions(dims)
	, mHighlighted(false)
{
	SetName(name);
}

Button::~Button()
{
	if (mNameTex)
	{
		SDL_DestroyTexture(mNameTex);
		delete mNameTex;
	}
}

void Button::SetName(const std::string& name)
{
	mName = name;

	if (mNameTex)
	{
		SDL_DestroyTexture(mNameTex);
		delete mNameTex;
		mNameTex = nullptr;
	}
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
		pt.x >(mPosition.x + mDimensions.x / 2.0f) ||
		pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
		pt.y >(mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	// Call attached handler, if it exists
	if (mOnClick)
	{
		mOnClick();
	}
}