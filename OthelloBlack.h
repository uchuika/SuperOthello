
#pragma once
#include "Actor.h"

class OthelloBlack : public Actor
{
public:
	OthelloBlack(class Game* game);
	void UpdateActor(float deltaTime) override;
};