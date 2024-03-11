#include "CrushPlatformFactory.h"

#include "../CrushPlatform.h"

Platform* CrushPlatformFactory::CreatePlatform() const
{
    return new CrushPlatform();
}
