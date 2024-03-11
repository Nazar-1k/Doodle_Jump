#include "Abilitie.h"
#include "../Sprites/GameSprite.h"

#include "../Sprites/Player/Player.h"


Ability::~Ability()
{
    DestroyAbility();
}

void Ability::Activate()
{
    isDestroy = true;
}

void Ability::Update(float DeltaTime, Player* MyPlayer)
{
    AbilitySprite->DrawSprite();
    
    // Check Colision With Player
    if (!MyPlayer->IsDie() && !MyPlayer->IsJetpack() && 
    IsColeected(MyPlayer->GetX(), MyPlayer->GetY(), 
    static_cast<float>(MyPlayer->GetWidth()), static_cast<float>(MyPlayer->GetHeight())))
    {
        Activate();
    }

    // MoveDown 
    if (MyPlayer->IsWithinMaxJumpHeight())
    {
        MoveDown(MyPlayer->GetDy(), DeltaTime);
    }
}

void Ability::DestroyAbility()
{
    AbilitySprite->DestroySprite();
}

bool Ability::IsColeected(float OtherX, float OtherY, float OtherHeight, float OtherWidth)
{
    float x = AbilitySprite->GetX();
    float y = AbilitySprite->GetY();

    float Width = static_cast<float>(AbilitySprite->GetSpriteWidth());
    float Height = static_cast<float>(AbilitySprite->GetSpriteHeight());

    // Determine the coordinates of the upper, lower, left and right borders of the platform
    float Top = y - Height / 2;
    float Bottom = y + Height / 2;
    float Left = x - Width / 2;
    float Right = x + Width / 2;

    // Determine the coordinates of the upper, lower, left and right borders of another object
    float OtherTop = OtherY - OtherHeight / 2;
    float OtherBottom = OtherY + OtherHeight / 2;
    float OtherLeft = OtherX - OtherWidth / 2;
    float OtherRight = OtherX + OtherWidth / 2;

    // Check for collisions along both axes
    if (Bottom >= OtherTop && Top <= OtherBottom && Right >= OtherLeft && Left <= OtherRight)
    {
        return true;
    }
    return false;
}

void Ability::MoveDown(float PlayerDy, float DeltaTime)
{
    float x = AbilitySprite->GetX();
    float y = AbilitySprite->GetY();
    y -= PlayerDy * DeltaTime;

    AbilitySprite->SetPosition(x, y);
}

float Ability::GetY() const
{
    return AbilitySprite->GetY();
}
