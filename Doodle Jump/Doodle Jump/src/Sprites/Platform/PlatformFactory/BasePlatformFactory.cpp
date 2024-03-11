#include "BasePlatformFactory.h"

#include "../BasePlatform.h"

Platform* BasePlatformFactory::CreatePlatform() const
{
    return new BasePlatform();
}
