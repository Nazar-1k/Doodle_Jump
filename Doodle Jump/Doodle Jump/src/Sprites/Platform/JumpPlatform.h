#pragma once

#include "Platform.h"

class JumpPlatform : public Platform
{
public:
    virtual bool InitPlatform() override;

    virtual void UpdatePlatform(float DeltaTime, Player* MyPlayer) override;

    virtual ~JumpPlatform() {}

private:
    
    float JumpCoef = 3.f;
};

