#include "CrushPlatform.h"

#include "../GameSprite.h"
#include "../Player/Player.h"

static const char pathCrushPlatform [] = "data/Platform/CrushPlatformDefault.png";

bool CrushPlatform::InitPlatform()
{
	if (PlatformSprite = new GameSprite())
	{
		PlatformSprite->CreateSprite(pathCrushPlatform);
		return true;
	}

	return false;
}

void CrushPlatform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
	Platform::UpdatePlatform(DeltaTime, MyPlayer);

	if (!MyPlayer->IsDie() && CheckCollision(MyPlayer))
	{
		bDestroy = true;
	}
}
