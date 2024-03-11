#include "HalfCrushPlatformFactory.h"

#include "../HalfCrushPlatform.h"

Platform* HalfCrushPlatformFactory::CreatePlatform() const
{
    return new HalfCrushPlatform();
}
