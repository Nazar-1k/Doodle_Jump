#pragma once

#include "PlatformFactory.h"

class CrushPlatformFactory : public PlatformFactory
{
public:

	Platform* CreatePlatform() const override;
};

