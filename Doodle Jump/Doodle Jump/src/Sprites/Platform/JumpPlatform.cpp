#include "JumpPlatform.h"

#include "../GameSprite.h"
#include "../Player/Player.h"

static const char pathJumpPlatform[] = "data/Platform/JumpPlatform.png";

bool JumpPlatform::InitPlatform()
{
	if (PlatformSprite = new GameSprite())
	{
		PlatformSprite->CreateSprite(pathJumpPlatform);
		return true;
	}

	return false;
}

void JumpPlatform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
	Platform::UpdatePlatform(DeltaTime, MyPlayer);

	if (!MyPlayer->IsDie() && CheckCollision(MyPlayer))
	{
		MyPlayer->Jump(GetY(), static_cast<float>(GetHeight()), JumpCoef);
	}
}
