#include "Shield.h"

#include "../Framework/GameFarmework.h"

#include "../Sprites/GameSprite.h"

#include "../Timer/Timer.h"

static const char pathShield[] = "data/Shields/shield.png";

Shield::Shield(GameFramework& GameFrameworkRef)
:MyGameFramework { GameFrameworkRef }
{
	if (ShieldSprite = new GameSprite())
	{
		ShieldSprite->CreateSprite(pathShield);
	}

	ActiveShield();
}

Shield::~Shield()
{
	if (ShieldTimer)
	{
		delete ShieldTimer;
	}

	ShieldSprite->DestroySprite();

}

void Shield::UpdateShield(float newX, float newY, float DeltaTime, bool& bActive)
{
	ShieldSprite->SetPosition(newX, newY);

	ShieldSprite->DrawSprite(MyGameFramework.GetScreenWitdth());

	if (ShieldTimer->isStarted() && ShieldTimer->GetTime() >= CountShieldTime)
	{
		ShieldTimer->Pause();

		bActive = isActive = false;
	}

}

void Shield::ActiveShield()
{
	if (!ShieldTimer)
	{
		ShieldTimer = new Timer();
	}

	ShieldTimer->Start();

	isActive = true;
}
