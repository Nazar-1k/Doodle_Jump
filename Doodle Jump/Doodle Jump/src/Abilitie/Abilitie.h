#pragma once

class GameSprite;
class GameFramework;

class Player;

class Ability
{
public:
	Ability(GameFramework& GameFrameWorkRef) : MyGameFramework(GameFrameWorkRef), AbilitySprite { nullptr } {}
	virtual ~Ability();

	virtual void Activate();
	void Update(float DeltaTime, Player* myPlayer);
	void DestroyAbility();

	bool IsColeected(float OtherX, float OtherY, float OtherHeight, float OtherWidth);
	 
	void MoveDown(float PlayerDy, float DeltaTime);

public:

	bool IsDestroy() const  { return isDestroy; }

	float GetY() const;

protected:

	bool isDestroy = false;

	GameSprite* AbilitySprite;

	GameFramework& MyGameFramework;
};
