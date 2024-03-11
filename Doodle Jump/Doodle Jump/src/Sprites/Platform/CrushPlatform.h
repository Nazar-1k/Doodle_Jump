#pragma once

#include "Platform.h"

class CrushPlatform : public Platform
{
public:
    virtual bool InitPlatform() override;

    virtual void UpdatePlatform(float DeltaTime, Player* MyPlayer) override;

    virtual ~CrushPlatform() {}

};

