#include "GameBackground.h"

#include <iostream>
#include "Framework.h"

#include "../Text/Text.h"


// Buny Sets
static const char BunyBackgroundPath[] = "data/Backgrounds/Hop/hop-bck@2x.png";
static const char BunyBottomBackgroundPath[] = "data/Bottom/Hop/hop-bottom@2x.png";
static const char BunyTopBackgroundPath[] = "data/Score top/Hop/HopTop.png";
static const char BunyPlatformIconPath[] = "data/Platform/SmallBlackPlatform.png";

GameBackground::~GameBackground()
{
	DestroyBackground();
}

bool GameBackground::InitBackground(int ScreenWidth, int ScreenHeight)
{
	// Create Sprite for Background
	TopBackgroundSprite = createSprite(BunyTopBackgroundPath);
	BackgroundSprite = createSprite(BunyBackgroundPath);
	BottomBackgroundSprite = createSprite(BunyBottomBackgroundPath);

	// Create Platform Icon
	PlatformIconSprite = createSprite(BunyPlatformIconPath);

	// Create and init Text 
	ScoreText = new Text();
	CountPlatformText = new Text();

	ScoreText->InitText(XScoreText, YScoreText);
	CountPlatformText->InitText(XCountPlatformText, YCountPlatformText);

	if (BackgroundSprite && BottomBackgroundSprite && TopBackgroundSprite && ScoreText && CountPlatformText && PlatformIconSprite)
	{
		// Set Sprite Size
		setSpriteSize(BackgroundSprite, ScreenWidth, ScreenHeight);

		SetProportionSpriteSize(TopBackgroundSprite, ScreenWidth, ScreenHeight);
		SetProportionSpriteSize(BottomBackgroundSprite, ScreenWidth, ScreenHeight);

		return true;
	}

	std::cout << "Background init error";
	return false;
}


void GameBackground::DrawBackground()
{
	drawSprite(BackgroundSprite, XBackground, YBackground);
}

void GameBackground::DrawTopAndDownBackround(int NewScore, int NewCountPlatform)
{
	// Daraw Top/Bottom Bagraund
	drawSprite(BottomBackgroundSprite, XBottomBackground, YBottomBackground);
	drawSprite(TopBackgroundSprite, XTopBackground, YTopBackground);

	// Set Text
	ScoreText->UpdateText(NewScore);
	CountPlatformText->UpdateText(NewCountPlatform);

	drawSprite(PlatformIconSprite, XPlatformIcon, YPlatformIcon);
}

void GameBackground::DestroyBackground()
{
	destroySprite(BackgroundSprite);
	destroySprite(BottomBackgroundSprite);
	destroySprite(TopBackgroundSprite);
	destroySprite(PlatformIconSprite);

	if (ScoreText)
	{
		delete ScoreText;

	}

	if (CountPlatformText)
	{
		delete CountPlatformText;
	}
}




void GameBackground::SetProportionSpriteSize(Sprite* Sprite, int ScreenWidth, int ScreenHeight)
{
	// Get the initial dimensions of the sprite
	int StartSpriteWidth, StartSpriteHeight;
	getSpriteSize(Sprite, StartSpriteWidth, StartSpriteHeight);

	int TargetWidth = ScreenWidth;

	// Calculate the new proportional height
	int NewHeight = static_cast<int>((TargetWidth * StartSpriteHeight) / StartSpriteWidth);

	setSpriteSize(Sprite, TargetWidth, NewHeight);
	if (BottomBackgroundSprite)
	{
		// Set the position vertically
		YBottomBackground = ScreenHeight - NewHeight;
	}

}
