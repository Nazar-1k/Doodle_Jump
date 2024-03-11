#include "AnimSprite.h"

#include "../Sprites/GameSprite.h"

AnimSprite& AnimSprite::operator=(const AnimSprite& other)
{
	if (this != &other)
	{
		this->SpriteDefault = other.SpriteDefault;
		this->SpriteJump = other.SpriteJump;
		this->SpriteDie = other.SpriteDie;
	}

	return *this;
}

bool AnimSprite::CreateSprites(const char* pathSpriteDefault, const char* pathSpriteJump, const char* pathSpriteDie)
{
	// Init Sprite
	if ((SpriteDefault = new GameSprite()) && (SpriteJump = new GameSprite()) && (SpriteDie = new GameSprite()))
	{
		SpriteDefault->CreateSprite(pathSpriteDefault);
		SpriteJump->CreateSprite(pathSpriteJump);
		SpriteDie->CreateSprite(pathSpriteDie);

		return true;
	}
	else
	{
		return false;
	}
}

void AnimSprite::DestroySprites()
{
	SpriteDefault->DestroySprite();
	SpriteJump->DestroySprite();
	SpriteDie->DestroySprite();
}