#pragma once

#include "PlatformFactory.h"

class JumpPlatformFactory : public PlatformFactory
{
public:

	Platform* CreatePlatform() const override;
};

