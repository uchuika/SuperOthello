#include "SpriteComponent.h"
#include "OthelloBlack.h"
#include "Game.h"

OthelloBlack::OthelloBlack(class Game* game)
:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture("Assets/OthelloBlack64.png"));
}

void OthelloBlack::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);


}