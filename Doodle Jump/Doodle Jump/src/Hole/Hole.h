#pragma once

class GameSprite;
class Player;

class Hole
{
public:

	virtual ~Hole();

	virtual void Update(float DeltaTime, Player* MyPlayer);
	bool CheckColision(Player* MyPlayer);
	
	void SetPosition(float x, float y);

	bool IsDestroy() { return false; }

	float GetY() const;
	float GetX() const;

	float GetWidth() const;

protected:

	GameSprite* HoleSprite = nullptr; 
	
	float MaxForce = 0.5;


private:

	void MoveDown(float DeltaTime,float PlayerDy);

	
};
