#include "Enemy.h"

#include <iostream>
#include <cstdlib> 
#include <ctime>

#include "../GameSprite.h"

#include "../Player/Player.h"
#include "../Bullet/Bullet.h"

// Path Sprite
static const char PathEnemy1[] = "data/Enemy/BigEnemy.png";
static const char PathEnemy2[] = "data/Enemy/MediumEnemy.png";
static const char PathEnemy3[] = "data/Enemy/SmallEnemy.png";

Enemy::Enemy(float x, float y)
{
    InitEnemy(x, y);
}

Enemy::~Enemy()
{
    DestroyEnemy();
}
void Enemy::DestroyEnemy()
{
    EnemySprite->DestroySprite();
}

void Enemy::InitEnemy(float x, float y)
{
    if (EnemySprite = new GameSprite())
    {
        int randomIndex = std::rand() % 3;

        switch (randomIndex)
        {
        case 0:
            EnemySprite->CreateSprite(PathEnemy1);
            break;
        case 1:
            EnemySprite->CreateSprite(PathEnemy2);
            break;
        case 2:
            EnemySprite->CreateSprite(PathEnemy3);
            break;
        }

        EnemySprite->SetPosition(x, y - EnemySprite->GetSpriteHeight() / 2);
        InitialX = EnemySprite->GetX();
    }
}

void Enemy::Update(float DeltaTime, Player* MyPlayer)
{
    // Left / Right Move
    MoveEnemy(DeltaTime);
    EnemySprite->DrawSprite();

    // MoveDown Enemy
    if (MyPlayer->IsWithinMaxJumpHeight())
    {
        MoveDown(MyPlayer->GetDy(), DeltaTime);
    }
    
    // Check Colision With Player
    bool isLoose = MyPlayer->IsDie();
    if (!MyPlayer->IsJetpack() && !MyPlayer->IsDie() && CheckPlayerCollision(MyPlayer->GetDy(), MyPlayer->GetX(), MyPlayer->GetY(), MyPlayer->GetWidth(), MyPlayer->GetHeight(), isLoose))
    {
        if (!isLoose)
        {
            float JumpCoef = 1.5f;
            MyPlayer->Jump(GetY(), static_cast<float>(GetHeight()), JumpCoef);
        }
        else
        {
            if (!MyPlayer->IsInvisible())
            {
                MyPlayer->SetDie(true);
            }
            else
            {
                bDestroy = true;
            }
        }
    }

    // Check Colision With Bullet
    std::vector<Bullet*> Bulletss = MyPlayer->GetBullets();
    if (!Bulletss.empty())
    {
        for (size_t j = 0; j < Bulletss.size(); j++)
        {
            if (CheckCollision(Bulletss[j]->GetX(), Bulletss[j]->GetY(), Bulletss[j]->GetWidth(), Bulletss[j]->GetHeight()))
            {
                Bulletss[j]->SetDestroyBullet();
                bDestroy = true;
            }
        }
    }
}


void Enemy::MoveDown(float PlayerDy, float DeltaTime)
{
    float x = EnemySprite->GetX();
    float y = EnemySprite->GetY();
    y -= PlayerDy * DeltaTime;

    EnemySprite->SetPosition(x, y);

}
void Enemy::MoveEnemy(float DeltaTime)
{
    float newX = EnemySprite->GetX() + Speed * DeltaTime;

    if (newX > InitialX + MoveRange || newX < InitialX - MoveRange)
    {

        Speed *= -1;
        newX = EnemySprite->GetX() + Speed * DeltaTime;
    }

    float newY = EnemySprite->GetY();

    EnemySprite->SetPosition(newX, newY);
}

float Enemy::GetY() const
{
    return EnemySprite->GetY();
}
float Enemy::GetHeight() const
{
    return static_cast<float>(EnemySprite->GetSpriteHeight());
}

bool Enemy::CheckCollision(float OtherX, float OtherY, int OtherWidth, int OtherHeight, float DoodleOffset)
{
    float x = EnemySprite->GetX();
    float y = EnemySprite->GetY();

    int Width = EnemySprite->GetSpriteWidth();
    int Height = EnemySprite->GetSpriteHeight();

    // Determine the coordinates of the upper, lower, left and right borders of the platform
    float Top = y - Height / 2;
    float Bottom = y + Height / 2;
    float Left = x - Width / 2;
    float Right = x + Width / 2;

    // Determine the coordinates of the upper, lower, left and right borders of another object
    float OtherTop = OtherY - OtherHeight / 2 + DoodleOffset;
    float OtherBottom = OtherY + OtherHeight / 2;
    float OtherLeft = OtherX - OtherWidth / 2 + DoodleOffset;
    float OtherRight = OtherX + OtherWidth / 2 - DoodleOffset;

    return Bottom >= OtherTop && Top <= OtherBottom && Right >= OtherLeft && Left <= OtherRight;
}
bool Enemy::CheckPlayerCollision(float OtherDy, float OtherX, float OtherY, int OtherHeight, int OtherWidth, bool& IsDead)
{
    float y = EnemySprite->GetY();
    int Height = EnemySprite->GetSpriteHeight();
    float Top = y - Height / 2;

    float OtherBottom = OtherY + OtherHeight / 2;
    float DoodleOffset = 30.f;

    // Check for collisions along both axes
    if (CheckCollision(OtherX, OtherY, OtherHeight, OtherWidth, DoodleOffset))
    {
        if (OtherDy >= 0 && Top + DoodleOffset >= OtherBottom && Top <= OtherBottom)
        {

            bDestroy = true;
            IsDead = false;
        }
        else
        {
            IsDead = true;
        }
     
        return true;
    }

    return false;
}
