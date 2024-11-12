#pragma once
#include "TextComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Font.h"

TextComponent::TextComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
	, mVisible(true)
	, mTextTex(nullptr)
{
	mOwner->GetGame()->AddText(this);
}

TextComponent::~TextComponent()
{
	mOwner->GetGame()->RemoveText(this);
}

void TextComponent::Draw(SDL_Renderer* renderer)
{
	DrawTexture(renderer, mTextTex, )
}

void TextComponent::SetText(const std::string& text)
{
	mText = text;

	if (mTextTex)
	{
		delete mTextTex;
		mTextTex = nullptr;
	}
	mTextTex = mFont->RenderText(mText);
}

void TextComponent::DrawTexture(class SDL_Renderer* renderer, class SDL_Texture* texture,
	const Vector2& offset = Vector2::Zero,
	float scale = 1.0f) 
{
	if (mTextTex)
	{
		if (mTextTex)
		{
			SDL_Rect r;
			// Scale the width/height by owner's scale
			r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
			r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
			// Center the rectangle around the position of the owner
			r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
			r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

			// Draw (have to convert angle from radians to degrees, and clockwise to counter)
			SDL_RenderCopyEx(renderer,
				mTextTex,
				nullptr,
				&r,
				-Math::ToDegrees(mOwner->GetRotation()),
				nullptr,
				SDL_FLIP_NONE);
		}
	}
}

void TextComponent::SetTexture(SDL_Texture* texture)
{
	mTextTex = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

