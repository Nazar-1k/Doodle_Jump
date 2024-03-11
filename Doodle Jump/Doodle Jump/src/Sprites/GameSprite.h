#pragma once

// If I could, I'd inherited from the Sprite class. 
class Sprite;

#include "../Point/Point.h"

class GameSprite
{
public:

	GameSprite();

	virtual ~GameSprite();
	void DestroySprite();

	virtual void CreateSprite(const char* path);

	// Simple DrawSprite
	virtual void DrawSprite();
	// Draw sprite with smoothly moving from one edge to another
	virtual void DrawSprite(int ScreenWidth);

public:
	// Get Sprite Size
	int GetSpriteWidth() const { return Width; }
	int GetSpriteHeight() const { return Height; }

	// Get Center Position
	float GetX() const { return Coord.x; };
	float GetY() const { return Coord.y; };

	float GetSecondX() const { return x + Width / 2; };

	Point GetCoord() const { return Coord; };
 
 public:

	// Set Sprite Size
	void SetSpriteSize(int NewWidth, int NewHeight);

	void SetPosition(float newX, float newY);
	void SetPosition(Point NewCoord);


protected:

	Sprite* MySprite;

	// Sprite coord (center Sprite)
	Point Coord;

	// Sprite X coord (for second display Sprite if out of the screen) 
	float x;
	bool isDrawTwoSprite = false;

	// Sprite Size
	int Width;
	int Height;
};

