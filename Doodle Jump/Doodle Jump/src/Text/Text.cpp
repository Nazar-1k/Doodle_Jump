#include "Text.h"

#include "../Sprites/GameSprite.h"
#include <string>

// Path for number Sprites
static const char pathNumber0[] = "data/Numbers/0.png";
static const char pathNumber1[] = "data/Numbers/1.png";
static const char pathNumber2[] = "data/Numbers/2.png";
static const char pathNumber3[] = "data/Numbers/3.png";
static const char pathNumber4[] = "data/Numbers/4.png";
static const char pathNumber5[] = "data/Numbers/5.png";
static const char pathNumber6[] = "data/Numbers/6.png";
static const char pathNumber7[] = "data/Numbers/7.png";
static const char pathNumber8[] = "data/Numbers/8.png";
static const char pathNumber9[] = "data/Numbers/9.png";

Text::~Text()
{
	DestroyText();
}

bool Text::InitText(float NewX, float NewY)
{

	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber0);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber1);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber2);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber3);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber4);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber5);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber6);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber7);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber8);
		Numbers.push_back(Number);
	}
	if (GameSprite* Number = new GameSprite())
	{
		Number->CreateSprite(pathNumber9);
		Numbers.push_back(Number);
	}

	// Set Position
	StartX = NewX;
	StartY = NewY;

	return true;
}

void Text::UpdateText(int Score)
{
	std::string numberString = std::to_string(Score);

	float CurrentX = StartX;

	// Output sprites for each digit of the number
	for (char digit : numberString)
	{
		// Convert the digit symbol to the corresponding sprite index (ASCII)
		int digitIndex = digit - '0';

		// Check if the index is within the sprite array
		if (digitIndex >= 0 && digitIndex < Numbers.size())
		{
			Numbers[digitIndex]->SetPosition(CurrentX, StartY);

			Numbers[digitIndex]->DrawSprite();
			CurrentX += Numbers[digitIndex]->GetSpriteWidth() + Spacing;
		}
	}
}

void Text::DestroyText()
{
	for (GameSprite* sprite : Numbers)
	{
		if (sprite)
		{
			delete sprite;
		}
	}
}

