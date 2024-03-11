#pragma once
#include "Platform.h"

class GameFramework;

class HalfCrushPlatform : public Platform
{
public:

    virtual bool InitPlatform() override;

    virtual void UpdatePlatform(float DeltaTime, Player* MyPlayer) override;

    virtual ~HalfCrushPlatform() {}
};

