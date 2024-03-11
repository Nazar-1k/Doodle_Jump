#include "HalfCrushPlatform.h"

#include "../GameSprite.h"
#include "../Player/Player.h"

static const char pathHalfCrushPlatform[] = "data/Platform/HalphCrushPlatform.png";

bool HalfCrushPlatform::InitPlatform()
{
	if (PlatformSprite = new GameSprite())
	{
		PlatformSprite->CreateSprite(pathHalfCrushPlatform);
		return true;
	}

	return false;
}

void HalfCrushPlatform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
	Platform::UpdatePlatform(DeltaTime, MyPlayer);

	if (!MyPlayer->IsDie() && CheckCollision(MyPlayer))
	{
		MyPlayer->Jump(GetY(), static_cast<float>(GetHeight()));

		bDestroy = true;
	}

}
