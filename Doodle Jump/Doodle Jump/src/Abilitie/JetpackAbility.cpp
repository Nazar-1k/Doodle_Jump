#include "JetpackAbility.h"
#include "../Sprites/GameSprite.h"

#include "../Framework/GameFarmework.h"
#include "../Sprites/Player/Player.h"

// path 
static const char pathAbility[] = "data/Achievement/Jetpack/ach-jetpack.png";

JetpackAbility::JetpackAbility(GameFramework& GameFrameWorkRef, float x, float y)
:Ability(GameFrameWorkRef)
{
	if (AbilitySprite = new GameSprite())
	{
		AbilitySprite->CreateSprite(pathAbility);
		AbilitySprite->SetPosition(x, y - AbilitySprite->GetSpriteHeight() / 2);
	}
}

void JetpackAbility::Activate()
{
	Ability::Activate();

	MyGameFramework.GetDoodlePlayer()->SetJetpack(true);
}
