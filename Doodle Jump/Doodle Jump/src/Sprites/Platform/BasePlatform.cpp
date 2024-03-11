#include "BasePlatform.h"

#include "../GameSprite.h"
#include "../Player/Player.h"

// Path 
static const char pathBasePlatform[] = "data/Platform/BasePlatform.png";

bool BasePlatform::InitPlatform()
{
	if (PlatformSprite = new GameSprite())
	{
		PlatformSprite->CreateSprite(pathBasePlatform);
		return true;
	}

	return false;
}

void BasePlatform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
	Platform::UpdatePlatform(DeltaTime, MyPlayer);

	if (!MyPlayer->IsDie() && CheckCollision(MyPlayer))
	{
		MyPlayer->Jump(GetY(), static_cast<float>(GetHeight()));
	}
}
