#pragma once

class GameSprite;

enum FAnimState
{
	Default,
	Jump,
	Die
};

struct AnimSprite
{
	GameSprite* SpriteDefault;
	GameSprite* SpriteJump;
	GameSprite* SpriteDie;

	FAnimState AnimState = FAnimState::Default;

	AnimSprite() :SpriteDefault{ nullptr }, SpriteJump{ nullptr }, SpriteDie{ nullptr } {};
	AnimSprite& operator=(const AnimSprite& other);

	bool CreateSprites(const char* pathSpriteDefault, const char* pathSpriteJump, const char* pathSpriteDie);
	void DestroySprites();
};
