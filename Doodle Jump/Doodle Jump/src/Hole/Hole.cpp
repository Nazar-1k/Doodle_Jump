#include "Hole.h"

#include "../Sprites/GameSprite.h"
#include "../Sprites/Player/Player.h"

Hole::~Hole()
{
	if (HoleSprite)
	{
		delete HoleSprite;
	}
}

void Hole::Update(float DeltaTime, Player* MyPlayer)
{
	HoleSprite->DrawSprite();

    // MoveDown 
    if (MyPlayer->IsWithinMaxJumpHeight())
    {
        MoveDown(MyPlayer->GetDy(), DeltaTime);
    }
}

bool Hole::CheckColision(Player* MyPlayer)
{
    float x = HoleSprite->GetX();
    float y = HoleSprite->GetY();

    float Width = static_cast<float>(HoleSprite->GetSpriteWidth());
    float Height = static_cast<float>(HoleSprite->GetSpriteHeight());

    // Determine the coordinates of the upper, lower, left and right borders of the platform
    float Top = y - Height / 2;
    float Bottom = y + Height / 2;
    float Left = x - Width / 2;
    float Right = x + Width / 2;

    // Determine the coordinates of the upper, lower, left and right borders of another object
    float OtherTop = MyPlayer->GetY() - static_cast<float>(MyPlayer->GetHeight() / 2);
    float OtherBottom = MyPlayer->GetY() + static_cast<float>(MyPlayer->GetHeight() / 2);
    float OtherLeft = MyPlayer->GetX() - static_cast<float>(MyPlayer->GetWidth() / 2);
    float OtherRight = MyPlayer->GetX() + static_cast<float>(MyPlayer->GetWidth() / 2);

    // Check for collisions along both axes
    if (Bottom >= OtherTop && Top <= OtherBottom && Right >= OtherLeft && Left <= OtherRight)
    {
        return true;
    }

    return false;
}

void Hole::SetPosition(float x, float y)
{
    HoleSprite->SetPosition(x, y);
}

float Hole::GetWidth() const
{
    return static_cast<float>(HoleSprite->GetSpriteWidth());
}

float Hole::GetY() const
{
    return HoleSprite->GetY();
}

float Hole::GetX() const
{
    return HoleSprite->GetX();
}

void Hole::MoveDown(float DeltaTime, float PlayerDy)
{
    float x = HoleSprite->GetX();
    float y = HoleSprite->GetY();
    y -= PlayerDy * DeltaTime;

    HoleSprite->SetPosition(x, y);
}
