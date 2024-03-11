#pragma once

#include "PlatformFactory.h"

class MovePlatformFactory : public PlatformFactory
{
public:

	Platform* CreatePlatform() const override;
};

