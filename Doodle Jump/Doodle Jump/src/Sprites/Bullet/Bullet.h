#pragma once

#include <memory>

class GameSprite;
class GameFramework;
class Timer;

class Bullet
{
public:

	Bullet(GameFramework& GameFrameworkRef, float StartX, float StartY);
	~Bullet();

	void SetStartPosition(float StartX, float StartY);
	void CalculateBulletMovementDirection(float StartX, float StartY);

	void UpdateBullet(float DeltaTime);
	bool IsDestroyed() { return isDestroyed; }

	void SetDestroyBullet();

	float GetX() const;
	float GetY() const;

	int GetHeight() const;
	int GetWidth() const;

private:

	float x = 0;
	float y = 0;

	float dx;
	float dy;

	float Speed = 10.f;

	Timer* TimerToDestroy;
	unsigned int CountTimeToDestroy = 3000;
	bool isDestroyed = false;

	GameSprite* BulletSprite;
	GameFramework& MyGameFramework;

	void Normalize(float& x, float& y);
};

