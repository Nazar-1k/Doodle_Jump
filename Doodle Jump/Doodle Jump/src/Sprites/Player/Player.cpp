#include "Player.h"

#include "../../Framework/GameFarmework.h"

#include "../GameSprite.h"
#include "../Bullet/Bullet.h"

#include "../../Jetpacks/Jetpack.h"
#include "../../Shield/Shield.h"

#include "../../Anim/AnimSprite.h"
#include "../../Timer/Timer.h"

#include <iostream>

// Left Sprites
static const char pathBunyLeftDefault[] = "data/Sprites/Doodle/Bunny Doodle/bunny-left@2x.png";
static const char pathBunyLeftJump[] = "data/Sprites/Doodle/Bunny Doodle/bunny-left-odskok@2x.png";

// Right Sprites
static const char pathBunyRightDefault[] = "data/Sprites/Doodle/Bunny Doodle/bunny-right@2x.png";
static const char pathBunyRightJump[] = "data/Sprites/Doodle/Bunny Doodle/bunny-right-odskok@2x.png";

// Shot Sprites Up
static const char pathBunyShotUpDefault[] = "data/Sprites/Doodle/Bunny Doodle/bunny-puca@2x_up.png";
static const char pathBunyShotUpJump[] = "data/Sprites/Doodle/Bunny Doodle/bunny-puca-odskok@2x_up.png";

// Sprites Die
static const char pathBunyDieLeft[] = "data/Sprites/Doodle/Bunny Doodle/bunny-left_Die.png";
static const char pathBunyDieRight[] = "data/Sprites/Doodle/Bunny Doodle/bunny-right_Die.png";

Player::Player(GameFramework& GameFrameworkRef)
	: MyGameFramework{ GameFrameworkRef },
	LeftSprite{ nullptr }, RightSprite{ nullptr }, ShotUpSprite{ nullptr }, MainSprite{ nullptr },
	ShotTimer{ nullptr }, JumpTimer{ nullptr }, StopAnimShotTimer{ nullptr }
{
	InitSprites();
}

Player::~Player()
{
	DestroySprites();

	if (MainSprite) 
	{
		delete MainSprite;
	}

	if (ShotTimer) 
	{
		delete ShotTimer;
	}

	if (StopAnimShotTimer)
	{
		delete StopAnimShotTimer;
	}

	if (JumpTimer) 
	{
		delete JumpTimer;
	}

	if (AbilityJetpack)
	{
		delete AbilityJetpack;
	}

	if (!Bullets.empty()) 
	{
		for (auto bullet : Bullets) 
		{
			if (bullet != nullptr)
			{
				delete bullet;
			}
		}

		Bullets.clear();
	}
}

void Player::DestroySprites()
{
	if (LeftSprite || RightSprite || ShotUpSprite)
	{
		LeftSprite->DestroySprites();
		RightSprite->DestroySprites();
		ShotUpSprite->DestroySprites();
	}
}

bool Player::InitSprites()
{
	// Init Left Sprite
	if (LeftSprite = new AnimSprite())
	{
		if (!LeftSprite->CreateSprites(pathBunyLeftDefault, pathBunyLeftJump, pathBunyDieLeft))
			return false;
	}

	// Init Right Sprite
	if (RightSprite = new AnimSprite())
	{
		if (!RightSprite->CreateSprites(pathBunyRightDefault, pathBunyRightJump, pathBunyDieRight))
			return false;
	}

	// Init Shot Up Sprite
	if (ShotUpSprite = new AnimSprite())
	{
		if (!ShotUpSprite->CreateSprites(pathBunyShotUpDefault, pathBunyShotUpJump, pathBunyDieRight))
			return false;
	}

	if (MainSprite = new AnimSprite())
	{
		if (MainSprite)
		{
			*MainSprite = *LeftSprite;

			StartWidth = Width = MainSprite->SpriteDefault->GetSpriteWidth();
			StartHeight = Height = MainSprite->SpriteDefault->GetSpriteHeight();
		}
	}


	MaxDoodleJumpHeight = static_cast<int>(MyGameFramework.GetScreenHeight() * ScreenJumpHeightRatio);


	ShotTimer = new Timer();
	StopAnimShotTimer = new Timer();
	JumpTimer = new Timer();

	if (!ShotTimer && !StopAnimShotTimer && !JumpTimer)
	{
		return false;
	}

	SetStartOptions();

	return true;
}
void Player::SetStartOptions()
{
	*MainSprite = *LeftSprite;

	dx = 0;
	dy = 0;

	SetPosition({ static_cast<float>(MyGameFramework.GetScreenWitdth() / 2) , static_cast<float>(MyGameFramework.GetScreenHeight() + Height) });
	SetSize(StartWidth, StartHeight);

	bJetpack = false;
	
	bDie = false;
	CanMove = true;

	bInvisible = false;
	bShield = false;
}

void Player::DrawSprite(float DeltaTime, bool& isLoose)
{
	UpdateSprite(DeltaTime, isLoose);

	switch (MainSprite->AnimState)
	{
	case FAnimState::Default:
		MainSprite->SpriteDefault->DrawSprite(MyGameFramework.GetScreenWitdth());
		break;

	case FAnimState::Jump:
		MainSprite->SpriteJump->DrawSprite(MyGameFramework.GetScreenWitdth());
		break;

	case FAnimState::Die:
		MainSprite->SpriteDie->DrawSprite(MyGameFramework.GetScreenWitdth());
		break;

	default:
		break;
	}

	UpdateBullets(DeltaTime);
}
void Player::UpdateSprite(float DeltaTime, bool& isLoose)
{
	GetMainSpriteSize();

	LooseCondition(isLoose);

	UpdateMove(DeltaTime);

	HandlePlayerActions(DeltaTime);

	ShootCondition();
	JumpCondition();
	JetpackCondition(DeltaTime);
	ShieldCondition(DeltaTime);

	SetPosition(Coord);
}

void Player::Shot()
{
	if (!bJetpack && !bDie)
	{
		Bullet* newBullet = new Bullet(MyGameFramework, Coord.x, Coord.y - Height / 2);
		if (newBullet)
		{
			Bullets.push_back(newBullet);
		}
	}
}
void Player::Jump(float OtherY, float otheHeight, float JumpÑoefficient)
{
	if (canJump)
	{
		if (otheHeight != 0)
		{
			Coord = MainSprite->SpriteDefault->GetCoord();
			Coord.y = static_cast<float>(OtherY - otheHeight / 2 - static_cast<float>(Height / 2));
			MainSprite->SpriteJump->SetPosition(Coord);
		}

		dy = JumpForce * JumpÑoefficient;
	
		MainSprite->AnimState = FAnimState::Jump;
		canJump = false;

		JumpTimer->Start();
	}
}

void Player::AddVelocity(float VelocityX, float VelocityY)
{
	dx += VelocityX;
	dy += VelocityY;
}

float Player::GetOtherX() const
{
	// By default, because this variable is needed to handle the jump (and bending is possible only in the Default state)
	return MainSprite->SpriteDefault->GetSecondX();
}

void Player::SetDy(float NewDy)
{
	dy = NewDy;
}
void Player::SetDx(float NewDx)
{
	dx = NewDx;
}

void Player::SetCanMove(bool NewCanMove)
{
	CanMove = NewCanMove;
}

void Player::SetPosition(Point NewCoord)
{
	switch (MainSprite->AnimState)
	{
	case FAnimState::Default:

		MainSprite->SpriteDefault->SetPosition(NewCoord);
		break;

	case FAnimState::Jump:

		MainSprite->SpriteJump->SetPosition(NewCoord);
		break;

	case FAnimState::Die:

		MainSprite->SpriteDie->SetPosition(NewCoord);
		break;
	}
}

void Player::SetSize(int NewHeight, int NewWidth)
{
	LeftSprite->SpriteDefault->SetSpriteSize(NewHeight, NewHeight);
	LeftSprite->SpriteJump->SetSpriteSize(NewHeight, NewHeight);
	LeftSprite->SpriteDie->SetSpriteSize(NewHeight, NewHeight);

	RightSprite->SpriteDefault->SetSpriteSize(NewHeight, NewHeight);
	RightSprite->SpriteJump->SetSpriteSize(NewHeight, NewHeight);
	RightSprite->SpriteDie->SetSpriteSize(NewHeight, NewHeight);

	ShotUpSprite->SpriteDefault->SetSpriteSize(NewHeight, NewHeight);
	ShotUpSprite->SpriteJump->SetSpriteSize(NewHeight, NewHeight);
	ShotUpSprite->SpriteDie->SetSpriteSize(NewHeight, NewHeight);

	Height = NewHeight;
	Width =	NewWidth;
}

void Player::SetJetpack(bool Jetpack)
{
	bJetpack = Jetpack;

	if(AbilityJetpack && bJetpack)
	{
		AbilityJetpack->ActiveJetpack();
	}
}
void Player::SetShield(bool Shield)
{
	bShield = Shield;

	if (AbilityShield && bShield)
	{
		AbilityShield->ActiveShield();
	}
}

float Player::CalculateMaxJumpHeight() const
{
	float Time = (-JumpForce) / (VelocityY);

	float JumpHeight = JumpForce * Time + (VelocityY * Time * Time) / 2;
	JumpHeight *= -1;

	return JumpHeight;
}

void Player::UpdateBullets(float DeltaTime)
{
	if (!Bullets.empty())
	{

		for (size_t i = 0; i < Bullets.size(); i++)
		{
			if (!Bullets[i]->IsDestroyed())
			{
				Bullets[i]->UpdateBullet(DeltaTime);
			}
			else
			{
				delete Bullets[i];
				Bullets.erase(Bullets.begin() + i);
			}
		}
	}
}

void Player::UpdateMove(float DeltaTime)
{
	if (CanMove)
	{
		dy += VelocityY * DeltaTime;

		Coord.y += dy * DeltaTime;
		Coord.x += dx * DeltaTime;

		if (dx > MaxVelocityX)
		{
			dx = MaxVelocityX;
		}

		if (dx < -MaxVelocityX)
		{
			dx = -MaxVelocityX;
		}

		if (IsWithinMaxJumpHeight())
		{
			Coord.y = static_cast<float>(MaxDoodleJumpHeight);
		}
	}
}

void Player::GetMainSpriteSize()
{
	switch (MainSprite->AnimState)
	{
	case FAnimState::Default:
		Coord = MainSprite->SpriteDefault->GetCoord();

		if (!bUpdateSprite)
		{
			Width = MainSprite->SpriteDefault->GetSpriteWidth();
			Height = MainSprite->SpriteDefault->GetSpriteHeight();

			bUpdateSprite = true;
		}
		break;
	case FAnimState::Jump:

		Coord = MainSprite->SpriteJump->GetCoord();

		if (!bUpdateSprite)
		{
			Width = MainSprite->SpriteJump->GetSpriteWidth();
			Height = MainSprite->SpriteJump->GetSpriteHeight();

			bUpdateSprite = true;
		}
		break;

	case FAnimState::Die:

		Coord = MainSprite->SpriteDie->GetCoord();

		if (!bUpdateSprite)
		{
			Width = MainSprite->SpriteDie->GetSpriteWidth();
			Height = MainSprite->SpriteDie->GetSpriteHeight();

			bUpdateSprite = true;
		}
		break;

	}
}

void Player::LooseCondition(bool& isLoose)
{
	if (Coord.y + static_cast<float>(Height / 2) >= MyGameFramework.GetScreenHeight() && dy <= 0)
	{
		Jump(static_cast<float>(MyGameFramework.GetScreenHeight()), 0.f, 1.3f);
		isLoose = false;
	}
	else if (Coord.y + static_cast<float>(Height / 2) >= MyGameFramework.GetScreenHeight() && dy >= 0)
	{
		isLoose = true;
		bDie = true;
	}

	if (bDie)
	{
		MainSprite->AnimState = FAnimState::Die;
	}
}
void Player::ShootCondition()
{
	if (!canShoot && ShotTimer->isStarted() && ShotTimer->GetTime() >= static_cast<unsigned int>(ShootDalay))
	{
		canShoot = true;

		ShotTimer->Pause();
		StopAnimShotTimer->Start();

	}
	else if (StopAnimShotTimer->isStarted() && StopAnimShotTimer->GetTime() >= static_cast<unsigned int>(StopAnimShootDalay))
	{
		StopAnimShotTimer->Stop();

		if (dx >= 0)
		{
			*MainSprite = *RightSprite;
		}
		else
		{
			*MainSprite = *LeftSprite;
		}
	}
}
void Player::JumpCondition()
{
	if (!bDie)
	{
		if (!canJump && JumpTimer->isStarted() && JumpTimer->GetTime() >= static_cast<unsigned int>(JumpDalay))
		{
			JumpTimer->Stop();
			canJump = true;
		}

		// Return Sprite to defaoult state after jump
		if (dy >= VerticalThreshold && MainSprite->AnimState != FAnimState::Default)
		{
			MainSprite->AnimState = FAnimState::Default;
		}
	}
}
void Player::JetpackCondition(float DeltaTime)
{
	if (bJetpack)
	{
		if (!AbilityJetpack)
		{
			AbilityJetpack = new Jetpack(MyGameFramework);
		}

		dy = JetpackForce;
		*MainSprite = *RightSprite;

		MainSprite->AnimState = FAnimState::Jump;

		AbilityJetpack->UpdateJetpack(Coord.x, Coord.y, DeltaTime, bJetpack);

	}
}
void Player::ShieldCondition(float DeltaTime)
{
	if (bShield)
	{
		if (!AbilityShield)
		{
			AbilityShield = new Shield(MyGameFramework);
		}
		
		AbilityShield->UpdateShield(Coord.x, Coord.y, DeltaTime, bShield);

		// Set Invisible if Shield is active
		bInvisible = bShield;
	}
}

void Player::HandlePlayerActions(float DeltaTime)
{
	if (canShoot && MyGameFramework.IsMouseButtonPressed(FRMouseButton::LEFT))
	{
		if (!ShotTimer->isStarted() || ShotTimer->isPaused())
		{
			Shot();

			// Start Shot Dalay Timer
			ShotTimer->Start();
			StopAnimShotTimer->Stop();
		}

		*MainSprite = *ShotUpSprite;
		canShoot = false;
	}
	else if (MyGameFramework.IsKeyPressed(FRKey::LEFT))
	{
		if (!bJetpack && canShoot && MainSprite != LeftSprite)
		{
			*MainSprite = *LeftSprite;
			bUpdateSprite = true;

		}

		dx -= VelocityX * DeltaTime;

		if (dx < -MaxVelocityX)
		{
			dx = -MaxVelocityX;
		}


	}
	else if (MyGameFramework.IsKeyPressed(FRKey::RIGHT))
	{
		if (!bJetpack && canShoot && MainSprite != RightSprite)
		{
			*MainSprite = *RightSprite;
			bUpdateSprite = true;
		}

		dx += VelocityX * DeltaTime;

		if (dx > MaxVelocityX)
		{
			dx = MaxVelocityX;
		}
	}
}
