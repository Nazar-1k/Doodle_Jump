#pragma once

class Platform;
class GameFrameWork;

class PlatformFactory
{
public:
    virtual Platform* CreatePlatform() const = 0;
    virtual ~PlatformFactory() {}
};
