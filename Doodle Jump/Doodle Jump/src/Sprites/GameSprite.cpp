#include "GameSprite.h"

#include "Framework.h"
#include <iostream>

GameSprite::GameSprite()
	: MySprite{ nullptr }, Coord{ 0,0 }, Width{ 0 }, Height{ 0 }, x{ 0 }
{}

GameSprite::~GameSprite()
{
	DestroySprite();
}
void GameSprite::DestroySprite()
{
	destroySprite(MySprite);
}

void GameSprite::CreateSprite(const char* path)
{
	MySprite = createSprite(path);
	if (MySprite)
	{
		getSpriteSize(MySprite, Width, Height);
	}
}

void GameSprite::DrawSprite()
{
	drawSprite(MySprite, static_cast<int>(Coord.x - Width / 2), static_cast<int>(Coord.y - Height / 2));
}
void GameSprite::DrawSprite(int SreenWidth)
{
	// Compute coordinates for displaying the sprite
	float DrawX = Coord.x - Width / 2;
	float DrawY = Coord.y - Height / 2;

	// Display the main sprite
	drawSprite(MySprite, static_cast<int>(DrawX), static_cast<int>(DrawY));

	// Check if the sprite goes out of the screen on the left
	if (DrawX <= 0)
	{
		// Calculate the offset from the beginning of the screen for displaying the sprite
		float deltaX = 0 - DrawX;
		x = SreenWidth - deltaX; // Compute new X position for displaying secondary sprite  

		// Move the sprite back onto the screen if it completely disappears
		if (DrawX + Width <= 0)
		{
			// Set x for the main sprite from the secondary sprite
			Coord.x = x + Width / 2;
		}

		// Display the secondary sprite
		drawSprite(MySprite, static_cast<int>(x), static_cast<int>(DrawY));

		isDrawTwoSprite = true;
	}
	// Check if the sprite goes out of the screen on the right
	else if (DrawX + Width >= SreenWidth)
	{
		float deltaX = (DrawX + Width) - SreenWidth;
		x = 0 + deltaX - Width;

		if (DrawX >= SreenWidth)
		{

			Coord.x = x + Width / 2;
		}

		drawSprite(MySprite, static_cast<int>(x), static_cast<int>(DrawY));

		isDrawTwoSprite = true;
	}
	else
	{
		// Defind Not Posible for update varible
		x = -10000;
		isDrawTwoSprite = false;
	}
}

void GameSprite::SetSpriteSize(int NewWidth, int NewHeight)
{
	setSpriteSize(MySprite, NewWidth, NewHeight);

	Width = NewWidth;
	Height = NewHeight;
}

void GameSprite::SetPosition(float newX, float newY)
{
	Coord.x = newX;
	Coord.y = newY;
}
void GameSprite::SetPosition(Point NewCoord)
{
	Coord = NewCoord;
}
