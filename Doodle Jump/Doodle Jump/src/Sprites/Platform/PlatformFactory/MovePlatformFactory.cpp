#include "MovePlatformFactory.h"

#include "../MovePlatform.h"

Platform* MovePlatformFactory::CreatePlatform() const
{
    return new MovePlatform();
}
