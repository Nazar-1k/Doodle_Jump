#include "JumpPlatformFactory.h"

#include "../JumpPlatform.h"

Platform* JumpPlatformFactory::CreatePlatform() const
{
    return new JumpPlatform();;
}
