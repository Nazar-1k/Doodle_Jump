#pragma once

class Sprite;
class Text;

class GameBackground
{
public:

	~GameBackground();

	bool InitBackground(int ScreenWidth, int ScreenHeight);

	void DrawBackground();
	void DrawTopAndDownBackround(int NewScore, int NewCountPlatform);
	void DestroyBackground();


private:

	void SetProportionSpriteSize(Sprite* Sprite, int ScreenWidth, int ScreenHeight);

	Sprite* BackgroundSprite = nullptr;
	Sprite* BottomBackgroundSprite = nullptr;
	Sprite* TopBackgroundSprite = nullptr;

	Sprite* PlatformIconSprite = nullptr;

	// Text
	Text* ScoreText = nullptr;
	Text* CountPlatformText = nullptr;

	// Position Text
	float XScoreText = 30;
	float YScoreText = 30;

	float XCountPlatformText = 460;
	float YCountPlatformText = 30;

	// Position Backgraund Sprites
	int XTopBackground = 0;
	int YTopBackground = -1;

	int XBackground = 0;
	int YBackground = 0;

	int YBottomBackground = 0;
	int XBottomBackground = 0;

	// Position Platform Icon Sprite
	int XPlatformIcon = 380;
	int YPlatformIcon = 25;
};


