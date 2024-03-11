#pragma once

#include "PlatformFactory.h"

class GameFramework;

class HalfCrushPlatformFactory : public PlatformFactory
{
public:

    virtual Platform* CreatePlatform() const override;

};

