#pragma once

#include <vector>

class GameSprite;

class Player;
class Bullet;

class Enemy
{
public:
	Enemy(float x, float y);
	virtual ~Enemy();
	void DestroyEnemy();

	virtual void InitEnemy(float x, float y);
	void Update(float DeltaTime, Player* MyPlayer);

public:

	void MoveDown(float PlayerDy, float DeltaTime);
	void MoveEnemy(float DeltaTime);

public:

	float GetY() const;
	float GetHeight() const;

	bool CheckCollision(float OtherX, float OtherY, int OtherHeight, int OtherWidth, float DoodleOffset = 0);
	bool CheckPlayerCollision(float OtherDy, float OtherX, float OtherY, int OtherHeight, int OtherWidth, bool& IsDead);
	bool IsDestroy() const { return bDestroy; }

private:
	float bDestroy = false;

	float InitialX = 0;

	float Speed = 2.f;
	float MoveRange = 50.0f;

	GameSprite* EnemySprite = nullptr;
};

