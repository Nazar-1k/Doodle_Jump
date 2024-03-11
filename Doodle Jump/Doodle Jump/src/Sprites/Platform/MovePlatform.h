#pragma once

#include "Platform.h"

class MovePlatform : public Platform
{
public:
    virtual bool InitPlatform() override;

    virtual void UpdatePlatform(float DeltaTime, Player* MyPlayer) override;

    virtual ~MovePlatform() {}

private:
    
    void MovePLatform(float DeltaTime);

    float PlatformSpeed = 3.f;


};

