#include "Platform.h"

#include <iostream>

#include "../GameSprite.h"
#include "../Player/Player.h"

#include "../../Framework/GameFarmework.h"

Platform::~Platform()
{
    DestroyPlatform();
}

void Platform::DestroyPlatform()
{
    if (PlatformSprite)
    {
        PlatformSprite->DestroySprite(); 
    }
}

void Platform::UpdatePlatform(float DeltaTime, Player* MyPlayer)
{
    if (!bDestroy)
    {
        PlatformSprite->DrawSprite();

        if (MyPlayer->IsWithinMaxJumpHeight())
        {
            MoveDownPlatform(MyPlayer->GetDy(), DeltaTime);
        }
    }
}

void Platform::SetPosition(float x, float y)
{
    PlatformSprite->SetPosition(x, y);
}

bool Platform::CheckCollision(Player* MyPlayer)
{
    if (MyPlayer->GetDy() >= 0)
    {
        x = PlatformSprite->GetX();
        y = PlatformSprite->GetY();

        float Width = static_cast<float>(PlatformSprite->GetSpriteWidth());
        float Height = static_cast<float>(PlatformSprite->GetSpriteHeight());

        // Determine the coordinates of the upper, lower, left and right borders of the platform
        float Top = y - Height / 2;
        float Bottom = y + Height / 2;
        float Left = x - Width / 2;
        float Right = x + Width / 2;

        // Determine the coordinates of the upper, lower, left and right borders of another object
        float DoodleOffset = 30;
        float OtherTop = MyPlayer->GetY() - static_cast<float>(MyPlayer->GetHeight() / 2);
        float OtherBottom = MyPlayer->GetY() + static_cast<float>(MyPlayer->GetHeight() / 2);
        float OtherLeft1 = MyPlayer->GetX() - static_cast<float>(MyPlayer->GetWidth() / 2) + DoodleOffset;
        float OtherRight1 = MyPlayer->GetX() + static_cast<float>(MyPlayer->GetWidth() / 2) - DoodleOffset;

        float OtherLeft2 = MyPlayer->GetOtherX() - static_cast<float>(MyPlayer->GetWidth() / 2) + DoodleOffset;
        float OtherRight2 = MyPlayer->GetOtherX() + static_cast<float>(MyPlayer->GetWidth() / 2) - DoodleOffset;

        // Check for collisions along both axes
        if (Bottom >= OtherBottom && Top <= OtherBottom && Right >= OtherLeft1 && Left <= OtherRight1)
        {
            // A collision occurred
            return true;
        }
        else if (Bottom >= OtherBottom && Top <= OtherBottom && Right >= OtherLeft2 && Left <= OtherRight2)
        {
            return true;
        }

    }
    return false;
}

float Platform::GetX() const
{
    return PlatformSprite->GetX();
}

float Platform::GetY() const
{
    return PlatformSprite->GetY();
}

int Platform::GetHeight() const
{
    return static_cast<int>(PlatformSprite->GetSpriteHeight());
}

int Platform::GetWidth() const
{
    return static_cast<int>(PlatformSprite->GetSpriteWidth());
}

void Platform::MoveDownPlatform(float PlayerDy, float DeltaTime)
{
    x = PlatformSprite->GetX();
    y = PlatformSprite->GetY();
    y -= PlayerDy * DeltaTime;

    PlatformSprite->SetPosition(x, y);
}
