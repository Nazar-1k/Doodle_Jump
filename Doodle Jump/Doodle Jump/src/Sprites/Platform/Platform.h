#pragma once

class GameSprite;
class GameFramework;
class Player;

class Platform
{
public:
    virtual ~Platform();

    virtual bool InitPlatform() = 0;
    virtual void DestroyPlatform();

    virtual void UpdatePlatform(float DeltaTime, Player* MyPlayer);

    void SetPosition(float x, float y);

    bool CheckCollision(Player* MyPlayer);

    float GetX() const;
    float GetY() const;
    int GetHeight() const;
    int GetWidth() const;

    void MoveDownPlatform(float PlayerDy, float DeltaTime);

    bool IsDestroy() const { return bDestroy; }

protected:
    float x = 0;
    float y = 0;

    GameSprite* PlatformSprite;

    bool bDestroy = false;
};

