#pragma once

#include "PlatformFactory.h"

class BasePlatformFactory :public PlatformFactory
{
public:

    Platform* CreatePlatform() const override;
};

