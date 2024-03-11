#include "ShieldAbility.h"

#include "../Framework/GameFarmework.h"

#include "../Sprites/GameSprite.h"
#include "../Sprites/Player/Player.h"

// Path
static const char pathShieldAbility [] = "data/Shields/1shield.png";

ShieldAbility::ShieldAbility(GameFramework& GameFrameWorkRef, float x, float y)
:Ability(GameFrameWorkRef)
{
	if (AbilitySprite = new GameSprite())
	{
		AbilitySprite->CreateSprite(pathShieldAbility);
		AbilitySprite->SetSpriteSize(50,50);
		AbilitySprite->SetPosition(x, y - AbilitySprite->GetSpriteHeight() / 2);
	}

}

void ShieldAbility::Activate()
{
	if (!MyGameFramework.GetDoodlePlayer()->IsInvisible())
	{
		Ability::Activate();
		MyGameFramework.GetDoodlePlayer()->SetShield(true);
	}
}
