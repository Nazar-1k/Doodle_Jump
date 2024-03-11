#include "Bullet.h"

#include "../../Framework/GameFarmework.h"
#include "../GameSprite.h"
#include "../../Timer/Timer.h"

#include <iostream>
#include <cmath>

// Bullet Path
static const char pathBulet[] = "data/Projectiles/projectile-Egg@2x.png";

Bullet::Bullet(GameFramework& GameFrameworkRef, float StartX, float StartY)
	:x{ 0 }, y{ 0 }, dx{ 0.f }, dy{ 0.f },
	MyGameFramework{ GameFrameworkRef }
{
	// Create Bullet Sprite
	BulletSprite = new GameSprite();
	BulletSprite->CreateSprite(pathBulet);

	// Create and Start Timer
	TimerToDestroy = new Timer();
	TimerToDestroy->Start();

	SetStartPosition(StartX, StartY);


	CalculateBulletMovementDirection(StartX, StartY);
}
Bullet::~Bullet()
{
	BulletSprite->DestroySprite();

	if (TimerToDestroy)
	{
		delete TimerToDestroy;
	}
}

void Bullet::SetStartPosition(float StartX, float StartY)
{
	x = StartX;
	y = StartY;

	BulletSprite->SetPosition(x, y);
}
void Bullet::CalculateBulletMovementDirection(float StartX, float StartY)
{
	int TargetX;
	int TargetY;

	MyGameFramework.GetMousePosition(TargetX, TargetY);

	// If mouse position under Player, shot like in Original Doodle Jump
	if (TargetY >= StartY)
	{
		TargetY = static_cast<int>(StartY - TargetY);

		BulletSprite->DrawSprite(MyGameFramework.GetScreenWitdth());
	}

	dx = static_cast<float>(TargetX) - StartX;
	dy = static_cast<float>(TargetY) - StartY;

	Normalize(dx, dy);
}

void Bullet::UpdateBullet(float DeltaTime)
{
	if (!isDestroyed && BulletSprite)
	{
		if (TimerToDestroy->isStarted() && TimerToDestroy->GetTime() >= CountTimeToDestroy)
		{
			isDestroyed = true;
			return;
		}
		x = BulletSprite->GetX();
		y = BulletSprite->GetY();

		x += dx * Speed * DeltaTime;
		y += dy * Speed * DeltaTime;

		BulletSprite->SetPosition(x, y);
		BulletSprite->DrawSprite(MyGameFramework.GetScreenWitdth());
	}
}

void Bullet::SetDestroyBullet()
{
	isDestroyed = true;
}

float Bullet::GetX() const
{
	return BulletSprite->GetX();
}
float Bullet::GetY() const
{
	return BulletSprite->GetY();
}

int Bullet::GetHeight() const
{
	return BulletSprite->GetSpriteHeight();
}
int Bullet::GetWidth() const
{
	return BulletSprite->GetSpriteWidth();
}

void Bullet::Normalize(float& Vx, float& Vy)
{
	float Length = std::sqrt(Vx * Vx + Vy * Vy);
	if (Length != 0)
	{
		Vx /= Length;
		Vy /= Length;
	}
}
