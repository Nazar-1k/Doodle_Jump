#pragma once

#include <memory>

#include "vector"
#include "../../Point/Point.h"

class GameSprite;
class GameFramework;
class Timer;
class Bullet;
class Jetpack;
class Shield;

struct AnimSprite;



class Player
{
public:

	Player(GameFramework& GameFrameworkRef);
	~Player();

	void DestroySprites();

	bool InitSprites();
	void SetStartOptions();

	void DrawSprite(float DeltaTime, bool& isLoose);
	void UpdateSprite(float DeltaTime, bool& isLoose);

	void Shot();
	void Jump(float OtherY, float otheHeight = 0, float Jump—oefficient = 1);
	bool IsWithinMaxJumpHeight() const { return Coord.y <= MaxDoodleJumpHeight && dy <= 0; }

	float GetDx() const { return dx; }
	float GetDy() const { return dy; }
	void AddVelocity(float VelocityX, float VelocityY);

	float GetX() const { return Coord.x; }
	float GetY() const { return Coord.y; }

	// X on the other side screen, (when we move the player from one edge to another)
	float GetOtherX() const;

	int GetHeight() const { return Height; }
	int GetWidth() const { return Width; }

public:
	void SetDy(float NewDy);
	void SetDx(float NewDx);

	void SetCanMove(bool NewCanMove);

	void SetPosition(Point NewCoord);
	void SetSize(int NewHeight, int NewWidth);


	// Die functions
	void SetDie(bool Die) { bDie = Die; }
	bool IsDie() const { return bDie; }

	// Jetpack
	bool IsJetpack() const { return bJetpack; }
	void SetJetpack(bool Jetpack);

	// Shield
	bool IsShield() const { return bShield; }
	void SetShield(bool Shield);

	// Bullets
	std::vector<Bullet*> GetBullets() { return Bullets; }

	// Invisible
	bool IsInvisible() const { return bInvisible; } 

private:

	Point Coord{ 0, 0 };

	int Width = 0;
	int Height = 0;

	float dx = 0.f;
	float dy = 0.f;

	bool bDie = false;

	bool bInvisible = false;

	GameFramework& MyGameFramework;

	int StartWidth = 0;
	int StartHeight = 0;

	bool CanMove = true;
private:

	// Structs for Sprite 
	AnimSprite* LeftSprite;
	AnimSprite* RightSprite;
	AnimSprite* ShotUpSprite;

	// Main Sprite
	AnimSprite* MainSprite;

	// This Variable Check if need Update Sprite( if we move right or left )
	bool bUpdateSprite = false;

private:

	// Vertical threshold to disable the jump animation
	float VerticalThreshold = -5.f;

	// Veloxity
	float VelocityY = 0.2f;
	float VelocityX = 0.5f;
	float MaxVelocityX = 8.f;

private:

	// Force
	float JumpForce = -10.f;
	float JetpackForce = -10.f;

public:

	float CalculateMaxJumpHeight() const;

private:

	// Shot Timer
	Timer* ShotTimer;
	Timer* StopAnimShotTimer;
	bool canShoot = true;

	// Shoot Dalay in miliseconds
	const unsigned int ShootDalay = 300;

	// Return Sprite in default State after Shoot Dalay + this dalay in miliseconds
	const unsigned int StopAnimShootDalay = 200;

private:

	// Bullet
	std::vector<Bullet*> Bullets;
	void UpdateBullets(float DeltaTime);

private:

	// Jump Settings
	Timer* JumpTimer;
	bool canJump = true;
	int MaxDoodleJumpHeight;
	float ScreenJumpHeightRatio = 0.4f;

	// Jump Dalay in miliseconds
	const unsigned int JumpDalay = 100;

private:

	// Jetpack Ability
	bool bJetpack = false;
	Jetpack* AbilityJetpack;

private:
	
	// Shield Ability
	Shield* AbilityShield;
	bool bShield = false;

private:

	void UpdateMove(float DeltaTime);

	void GetMainSpriteSize();
	
	void LooseCondition(bool& isLoose);
	void ShootCondition();
	void JumpCondition();
	void JetpackCondition(float DeltaTime);
	void ShieldCondition(float DeltaTime);

	void HandlePlayerActions(float DeltaTime);
};

