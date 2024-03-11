#include "ScoreAbility.h"

#include "../Sprites/GameSprite.h"
#include "../Framework/GameFarmework.h"

static const char pathScoreAbility[] = "data/Achievement/Super Bouncer/ach-super-bouncer.png";

ScoreAbility::ScoreAbility(GameFramework& GameFrameWorkRef, float x, float y)
:Ability(GameFrameWorkRef)
{
	if (AbilitySprite = new GameSprite())
	{
		AbilitySprite->CreateSprite(pathScoreAbility);
		AbilitySprite->SetPosition(x, y - AbilitySprite->GetSpriteHeight() / 2);
	}
}

void ScoreAbility::Activate()
{
	Ability::Activate();

	MyGameFramework.AddScore(CountScoreAdd);
}
