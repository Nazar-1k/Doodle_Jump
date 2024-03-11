#include "BlackHole.h"

#include "../Sprites/GameSprite.h"

#include "../Sprites/Player/Player.h"
#include <iostream>

// Path
static const char pathBlackJole[] = "data/Hole/BlackHole.png";

BlackHole::BlackHole(float x, float y)
{
	if (HoleSprite = new GameSprite())
	{
		HoleSprite->CreateSprite(pathBlackJole);

		HoleSprite->SetPosition(x, y);
	}
    MaxForce = 5;
}

void BlackHole::Update(float DeltaTime, Player* MyPlayer)
{
   
    Hole::Update(DeltaTime, MyPlayer);

    if (!MyPlayer->IsJetpack() && CheckColision(MyPlayer))
    {
        float DistanceX = HoleSprite->GetX() - MyPlayer->GetX();
        float DistanceY = HoleSprite->GetY() - MyPlayer->GetY();
        float Distance = sqrt(DistanceX * DistanceX + DistanceY * DistanceY);

        // Calculate attraction force
        float forceMagnitude = MaxForce * (1 - Distance / HoleSprite->GetSpriteWidth() / 2);

        // Define attraction force direction
        float ForceDirectionX = DistanceX / Distance;
        float ForceDirectionY = DistanceY / Distance;

        if (Distance < 20.0f) 
        {
            // If the player is not at the center, move it to the center
            MyPlayer->SetPosition({ HoleSprite->GetX(), HoleSprite->GetY() });

            // And stop it
            MyPlayer->SetDy(0.f);
            MyPlayer->SetDx(0.f);

            if (PlayerWidth == 0 && PlayerHeight == 0)
            {

                PlayerWidth = static_cast<float>(MyPlayer->GetWidth());
                PlayerHeight = static_cast<float>(MyPlayer->GetHeight());
            }
            else
            {
                if(PlayerWidth >= 10 || PlayerHeight >= 10)
                { 
                    PlayerWidth -= PlayerResizeSpeed * DeltaTime;
                    PlayerHeight -= PlayerResizeSpeed * DeltaTime;
                    MyPlayer->SetSize(static_cast<int>(PlayerWidth), static_cast<int>(PlayerHeight));
                }
                else
                {
                    // Set Imposible Position for Loose game
                    MyPlayer->SetPosition({ 0.f, 10000.f });
                    MyPlayer->SetDy(1.f);
                    MyPlayer->SetCanMove(true);
                }
            }
        }
        else
        {
            // Apply attraction force to player's velocity
            float playerVelocityX = ForceDirectionX * forceMagnitude;
            float playerVelocityY = ForceDirectionY * forceMagnitude;

            MyPlayer->AddVelocity(playerVelocityX, playerVelocityY);
        }
    }
}
