#include "WhiteHole.h"

#include <math.h>

#include "../Sprites/GameSprite.h"
#include "../Sprites/Player/Player.h"

//Path 
static const char pathWhiteJole[] = "data/Hole/WhiteHole.png";

WhiteHole::WhiteHole(float x, float y)
{
	if (HoleSprite = new GameSprite())
	{
		HoleSprite->CreateSprite(pathWhiteJole);
		HoleSprite->SetPosition(x, y);
	}
    MaxForce = 5;
}

void WhiteHole::Update(float DeltaTime, Player* MyPlayer)
{
    Hole::Update(DeltaTime, MyPlayer);

    if (CheckColision(MyPlayer))
    {
        float DistanceX = HoleSprite->GetX() - MyPlayer->GetX();
        float DistanceY = HoleSprite->GetY() - MyPlayer->GetY();
        float Distance = static_cast<float>(sqrt(DistanceX * DistanceX + DistanceY * DistanceY));
        
        if (Distance < static_cast<float>(HoleSprite->GetSpriteWidth() / 2))
        {
            float forceMagnitude = MaxForce * (1 - Distance / HoleSprite->GetSpriteWidth() / 2);

            float ForceDirectionX = -DistanceX / Distance;
            float ForceDirectionY = -DistanceY / Distance;

            float playerVelocityX = ForceDirectionX * forceMagnitude;
            float playerVelocityY = ForceDirectionY * forceMagnitude;

            MyPlayer->AddVelocity(playerVelocityX, playerVelocityY);
        }
    }
}
