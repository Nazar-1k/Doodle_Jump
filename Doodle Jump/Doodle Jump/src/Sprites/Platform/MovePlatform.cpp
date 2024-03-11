#include "MovePlatform.h"

#include "../GameSprite.h"
#include "../Player/Player.h"

#include "Framework.h"

// Path 
static const char pathMovePlatform[] = "data/Platform/MovePlatform.png";

bool MovePlatform::InitPlatform()
{
	if (PlatformSprite = new GameSprite())
	{
		PlatformSprite->CreateSprite(pathMovePlatform);
		return true;
	}

	return false;
}

void MovePlatform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
	Platform::UpdatePlatform(DeltaTime, MyPlayer);

	MovePLatform(DeltaTime);

	if (!MyPlayer->IsDie() && CheckCollision(MyPlayer))
	{
		MyPlayer->Jump(GetY(), static_cast<float>(GetHeight()));
	}
}

void MovePlatform::MovePLatform(float DeltaTime)
{
	int SWidth;
	int SHeight;

	getScreenSize(SWidth, SHeight);
	x = PlatformSprite->GetX();

	x += PlatformSpeed * DeltaTime;

	if (x - static_cast<float>(PlatformSprite->GetSpriteWidth() / 2) < 0)
	{
		x = static_cast<float>(PlatformSprite->GetSpriteWidth() / 2);

		PlatformSpeed = -PlatformSpeed;
	}

	else if (x + static_cast<float>(PlatformSprite->GetSpriteWidth() / 2) > static_cast<float>(SWidth))
	{
		x = static_cast<float>(SWidth - PlatformSprite->GetSpriteWidth() / 2);

		PlatformSpeed = -PlatformSpeed;
	}

	PlatformSprite->SetPosition(x, PlatformSprite->GetY());
}
