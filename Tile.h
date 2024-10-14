#pragma once
// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include <vector>

class Tile : public Actor
{
public:
	friend class Grid;
	enum TileState
	{
		EDefault,
		EBlack,
		EWhite
	};

	Tile(class Game* game);

	void SetTileState(TileState state);
	TileState GetTileState() const { return mTileState; }
	void ToggleSelect();
	const Tile* GetParent() const { return mParent; }
private:
	// åoòHíTçıóp
	std::vector<Tile*> mAdjacent;
	Tile* mParent;
	float f;
	float g;
	float h;
	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;

	void UpdateTexture();
	class SpriteComponent* mSprite;
	TileState mTileState;
	bool mSelected;
};
