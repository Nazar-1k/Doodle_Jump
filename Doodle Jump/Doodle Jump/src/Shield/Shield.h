#pragma once

class GameSprite;
class GameFramework;
class Timer;

class Shield
{

public:
	Shield(GameFramework& GameFrameworkRef);
	~Shield();

	void UpdateShield(float x, float y, float DeltaTime, bool& bActive);

	void ActiveShield();

private:

	GameSprite* ShieldSprite;

	GameFramework& MyGameFramework;

	Timer* ShieldTimer;
	unsigned int CountShieldTime = 20'000; // 20 seconds

	bool isActive = false;

};

