#pragma once

#include <memory>

class GameSprite;
class GameFramework;
class Timer;

class Jetpack
{
public:
	Jetpack(GameFramework& GameFrameworkRef);
	~Jetpack();

	void UpdateJetpack(float x, float y, float DeltaTime, bool& bActive);
	void DestroySpriteJetpack();

	void ActiveJetpack();

private:

	int countFrame = 0;

	GameSprite* JetpackFrame1;
	GameSprite* JetpackFrame2;
	GameSprite* JetpackFrame3;

	GameFramework& MyGameFramework;
	
	Timer* JetpackTimer;
	unsigned int CountJetpackTime = 5000;

	float LeftJetpackOffset = 40.f;

	bool isActive = false;
	
};

